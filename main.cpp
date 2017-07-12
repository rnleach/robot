#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>

#include "timers.h"
#include "compile_time.h"
#include "custom_serial.h"

void init (void)
{
    serial_ascii_inout_init();
    // Set PIN09/PB1 as an output
    SET_BIT(DDRB, PB1);

    Timer1::set_mode(Timer1::Mode::FastPWM_InputTop);
    Timer1::set_prescaler(Timer1::Prescale::P8);
    Timer1::set_compare_match_PIN09(Timer1::CompareMatch::NonInverting); // PB1
    Timer1::set_frequency(50);
    Timer1::set_OCR1A(3390);
}

#define MAXT 5100
#define MINT 1480
#define RANGE_DEGREES 180
#define INCREMENT_DEGREES 30
#define STEPSIZE ((MAXT - MINT)/(RANGE_DEGREES / INCREMENT_DEGREES))
#define DELAY 500

void set_position( uint16_t pw_count) {
    printf("pw_count = %u degrees = %u\n",
        pw_count, 
        (uint16_t)((float)(pw_count - MINT) / (MAXT - MINT) * RANGE_DEGREES + 0.05)
    );
    Timer1::set_OCR1A(pw_count);
}

void set_degrees( int8_t angle) {
    int16_t mapped_angle = angle + 90;
    if(mapped_angle < 0) mapped_angle = 0;

    uint16_t pw_count = (uint16_t)((float) mapped_angle / (float)(RANGE_DEGREES) * (MAXT - MINT) + 0.5) + MINT;
    
    if(pw_count > MAXT) pw_count = MAXT;
    if(pw_count < MINT) pw_count = MINT;

    printf("angle = %d mapped_angle = %d  pw_count = %u\n",
        angle,
        mapped_angle,
        pw_count
    );
    Timer1::set_OCR1A(pw_count);
}

int main (void)
{
    init();
    while(1){
        // printf("MAX      = %u\n", Timer1::get_max());
        // printf("TOP      = %u\n", Timer1::get_top());
        // printf("PRESCALE = %u\n", Timer1::get_prescale());

        printf("start count up\n");
        for(uint16_t pw_count = MINT; pw_count <= MAXT; pw_count += STEPSIZE) {
            set_position(pw_count);
            _delay_ms(DELAY);
        }

        printf("start count down\n");
        for(uint16_t pw_count = MAXT; pw_count >= MINT; pw_count -= STEPSIZE) {
            set_position(pw_count);
            _delay_ms(DELAY);
        }

        printf("start degrees up\n");
        for(int8_t angle = -90; angle <= 90; angle += 30) {
            set_degrees(angle);
            _delay_ms(DELAY);
        }

        printf("start degrees down\n");
        for(int8_t angle = 90; angle >= -90; angle -= 30) {
            set_degrees(angle);
            _delay_ms(DELAY);
        }
    }
}
