#include <avr/io.h>
#include <avr/cpufunc.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>

#include "timers.h"
#include "compile_time.h"
#include "custom_serial.h"
#include "servo.h"
#include "range_finder.h"
#include "my_arduino.h"
#include "timer.h"

void init (void)
{
    serial_ascii_inout_init();

    set_pin_mode(Pins::D12, DataDirection::OUT);
    set_pin_mode(Pins::D11_PWM, DataDirection::IN);

    Timer<Timers::T0>::set_mode(ModesT<Timers::T0>::MType::Normal);
    Timer<Timers::T1>::set_mode(ModesT<Timers::T1>::MType::Normal);
    Timer<Timers::T2>::set_mode(ModesT<Timers::T2>::MType::CTC);

    Timer<Timers::T0>::set_prescaler(PrescalerT<Timers::T0>::PType::P8);
    Timer<Timers::T1>::set_prescaler(PrescalerT<Timers::T1>::PType::P8);
    Timer<Timers::T2>::set_prescaler(PrescalerT<Timers::T2>::PType::P32);

    Timer<Timers::T2>::set_top(100);
}

#define MAXT 5100
#define MINT 1480
#define RANGE_DEGREES 180
#define INCREMENT_DEGREES 1
#define STEPSIZE ((MAXT - MINT)/(RANGE_DEGREES / INCREMENT_DEGREES))
#define DELAY 13

/*
Timer<0> t0;
Timer<1> t1;
Timer<2> t2;
*/


int main (void)
{
    init();
    auto servo = ServoSG90_Pin09(MINT, MAXT);
    while(1){
        printf("T0 count = %u\n", Timer<Timers::T0>::get_count());
        printf("T1 count = %u\n", Timer<Timers::T1>::get_count());
        printf("T2 count = %u\n", Timer<Timers::T2>::get_count());

        printf("T0 prescale = %u\n", Timer<Timers::T0>::get_prescale());
        printf("T1 prescale = %u\n", Timer<Timers::T1>::get_prescale());
        printf("T2 prescale = %u\n", Timer<Timers::T2>::get_prescale());

        printf("T0 mode = %d\n", static_cast<int>(Timer<Timers::T0>::get_mode()));
        printf("T1 mode = %d\n", static_cast<int>(Timer<Timers::T1>::get_mode()));
        printf("T2 mode = %d\n", static_cast<int>(Timer<Timers::T2>::get_mode()));

        printf("T0 max = %u\n", Timer<Timers::T0>::get_max());
        printf("T1 max = %u\n", Timer<Timers::T1>::get_max());
        printf("T2 max = %u\n", Timer<Timers::T2>::get_max());

        printf("T0 top = %u\n", Timer<Timers::T0>::get_top());
        printf("T1 top = %u\n", Timer<Timers::T1>::get_top());
        printf("T2 top = %u\n", Timer<Timers::T2>::get_top());

        printf("start degrees up\n");
        for(int8_t angle = -90; angle < 90; angle += INCREMENT_DEGREES) {
            servo.set_degrees(angle);
            _delay_ms(DELAY);
        }

        printf("start degrees down\n");
        for(int8_t angle = 90; angle > -90; angle -= INCREMENT_DEGREES) {
            servo.set_degrees(angle);
            _delay_ms(DELAY);
        }

        // Send trigger pulse
        // printf("Sending trigger pulse.\n");
        volatile uint16_t rolls = 0;
        volatile uint8_t rolled = 0;
        set_pin_value(Pins::D12, PinValue::LOW);
        _delay_us(2);
        set_pin_value(Pins::D12, PinValue::HIGH);
        _delay_us(10);
        set_pin_value(Pins::D12, PinValue::LOW);
        _delay_us(2);

        while(!is_pin_set(Pins::D11_PWM))
        {
            _NOP();
        }
        // volatile uint8_t cnt = Timer2::get_count();
        volatile uint16_t cnt = Timer<Timers::T1>::get_count();

        _delay_us(2);
        volatile uint16_t loops = 0;
        volatile uint16_t down_loops = 0;
        volatile uint16_t up_loops = 0;
        while(get_pin_value(Pins::D11_PWM) == PinValue::HIGH)
        {
            // volatile uint8_t new_cnt = Timer2::get_count();
            volatile uint16_t new_cnt = Timer<Timers::T1>::get_count();
            if( new_cnt < cnt){
                rolled = 1;
                down_loops++;
            } else if (new_cnt >= cnt && !!rolled) {
                rolls++;
                rolled = 0;
                up_loops++;
            }
            loops++;
        }
        // uint8_t sub_ticks = (Timer2::get_count() - cnt);
        // uint16_t ticks = rolls * 256 + sub_ticks;
        uint16_t curr_cnt = Timer<Timers::T1>::get_count();
        uint16_t sub_ticks = (curr_cnt - cnt);
        if(curr_cnt < cnt) sub_ticks -= Timer<Timers::T1>::get_max() - Timer<Timers::T1>::get_top();
        uint16_t ticks = rolls * (Timer<Timers::T1>::get_top() + 1) + sub_ticks;
        printf("Set high found at cnt = %u\n", cnt);
        printf("Looped on high = %u with down_loops = %u and up_loops = %u\n", loops, down_loops, up_loops);
        printf("Set low found! %u * %u + %u = %u\n", rolls, (Timer<Timers::T1>::get_top() + 1), sub_ticks,ticks);
        // uint32_t us = ticks * (32* 1000000UL / F_CPU);
        uint32_t us = static_cast<uint32_t>(ticks * (static_cast<float>(Timer<Timers::T1>::get_prescale()) * 1000000.0 / F_CPU));
        printf("ticks = %u\nprescale = %u\n", ticks,Timer<Timers::T1>::get_prescale());
        printf("multiplier = %f\n", (static_cast<float>(Timer<Timers::T1>::get_prescale()) * 1000000.0 / F_CPU));
        printf("us = %lu\n", us);
        printf("cm = %lu\n\n", us / 58);
        _delay_ms(2000);
    }
}
