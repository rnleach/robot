#include <avr/io.h>

#include "servo.h"
#include "compile_time.h"
#include "timer.h"

const uint16_t ServoSG90_Pin09::PULSE_FREQ = 50;
const int8_t ServoSG90_Pin09::MIN_DEG = -90;
const int8_t ServoSG90_Pin09::MAX_DEG = 90;

ServoSG90_Pin09::ServoSG90_Pin09(uint16_t mn_cnt, uint16_t mx_cnt): 
    min_pw_count_{mn_cnt}, max_pw_count_{mx_cnt}
{
    Timer<Timers::T1>::set_mode(ModesT<Timers::T1>::MType::FastPWM_InputTop);
    Timer<Timers::T1>::set_compare_match<Channels::A>(CompareMatchT<Timers::T1>::CType::NonInverting);
    Timer<Timers::T1>::set_frequency(50);
    Timer<Timers::T1>::set_ocr<Channels::A>(3000);

    // Set PIN09/PB1 as an output
    set_pin_mode(Pins::D09_PWM, DataDirection::OUT);
}

void ServoSG90_Pin09::set_position( uint16_t pw_count) {
    Timer<Timers::T1>::set_ocr<Channels::A>(pw_count);
}

void ServoSG90_Pin09::set_degrees( int8_t angle) {
    if( angle < -90) angle = -90;
    if( angle > 90) angle = 90;
    uint8_t mapped_angle = static_cast<uint8_t>(angle + 90);

    uint16_t pw_count = 
        static_cast<uint16_t>(
            static_cast<float>(mapped_angle) / 180.0 * (max_pw_count_ - min_pw_count_) + 0.5
        ) + min_pw_count_;
    
    if(pw_count > max_pw_count_) pw_count = max_pw_count_;
    if(pw_count < min_pw_count_) pw_count = min_pw_count_;

    Timer<Timers::T1>::set_ocr<Channels::A>(pw_count);
}