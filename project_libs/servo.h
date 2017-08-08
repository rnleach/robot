#ifndef ROBOT_SERVO_H_
#define ROBOT_SERVO_H_
/**************************************************************************************************
servo.h

A customized project library for managing servos..

Author: Ryan Leach
**************************************************************************************************/
#include <stdint.h>
#include "my_arduino.h"
#include "timer.h"

template<Pins P, Timers TN>
class ServoSG90 {
    static_assert(Pairing<P, TN>::valid,"Invalid pairing of pin and timer.");
    static_assert(!Pairing<P, TN>::valid,"Not implemented.");
};

template<Pins P>
class ServoSG90<P, Timers::T1> {
    static_assert(Pairing<P, Timers::T1>::valid,"Invalid pairing of pin and timer.");

    public:
        ServoSG90(
            typename TimerValueType<Timers::T1>::ValueType mn_cnt, 
            typename TimerValueType<Timers::T1>::ValueType mx_cnt);

        void set_position(typename TimerValueType<Timers::T1>::ValueType pw_count);
        void set_degrees(int8_t angle); // -90 -> +90

    private:
        typename TimerValueType<Timers::T1>::ValueType min_pw_count_, max_pw_count_;
};

template<Pins P>
ServoSG90<P, Timers::T1>::ServoSG90(
    typename TimerValueType<Timers::T1>::ValueType mn_cnt, 
    typename TimerValueType<Timers::T1>::ValueType mx_cnt) :
        min_pw_count_{mn_cnt}, max_pw_count_{mx_cnt}
{
    constexpr auto PAIRING = Pairing<P,Timers::T1>();
    static_assert(PAIRING.valid, "Invalid pairing of pin and timer.");

    Timer<Timers::T1>::set_mode(ModesT<Timers::T1>::MType::FastPWM_InputTop);
    Timer<Timers::T1>::set_compare_match<PAIRING.channel>(CompareMatchT<Timers::T1>::CType::NonInverting);
    Timer<Timers::T1>::set_frequency(50);
    Timer<Timers::T1>::set_ocr<PAIRING.channel>(3000);

    // Set P as an output
    set_pin_mode(P, DataDirection::OUT);
}

template<Pins P>
void ServoSG90<P, Timers::T1>::set_position(typename TimerValueType<Timers::T1>::ValueType pw_count)
{
    constexpr auto PAIRING = Pairing<P,Timers::T1>();
    static_assert(PAIRING.valid, "Invalid pairing of pin and timer.");

    Timer<Timers::T1>::set_ocr<PAIRING.channel>(pw_count);
}

template<Pins P>
void ServoSG90<P, Timers::T1>::set_degrees(int8_t angle)
{
    constexpr auto PAIRING = Pairing<P,Timers::T1>();
    static_assert(PAIRING.valid, "Invalid pairing of pin and timer.");

    if( angle < -90) angle = -90;
    if( angle > 90) angle = 90;
    uint8_t mapped_angle = static_cast<uint8_t>(angle + 90);

    uint16_t pw_count = 
        static_cast<uint16_t>(
            static_cast<float>(mapped_angle) / 180.0 * (max_pw_count_ - min_pw_count_) + 0.5
        ) + min_pw_count_;
    
    if(pw_count > max_pw_count_) pw_count = max_pw_count_;
    if(pw_count < min_pw_count_) pw_count = min_pw_count_;

    Timer<Timers::T1>::set_ocr<PAIRING.channel>(pw_count);
}

#endif
