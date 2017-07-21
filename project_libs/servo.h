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
class Servo {
    static_assert(Pairing<P, TN>::valid);

    public:
        Servo(typename TimerValueType<TN>::ValueType mn_cnt, typename TimerValueType<TN>::ValueType mx_cnt);

    private:
        typename TimerValueType<TN>::ValueType min_pw_count_, max_pw_count_;
};

// TODO: templatize this to work with pins, timers.
// Currently only works on PIN09.
class ServoSG90_Pin09 {
    public:
        ServoSG90_Pin09(uint16_t mn_cnt, uint16_t mx_cnt);
        void set_position(uint16_t pw_count);
        void set_degrees(int8_t angle); // -90 -> +90

    private:
        static const uint16_t PULSE_FREQ;
        static const int8_t MIN_DEG, MAX_DEG;
        uint16_t min_pw_count_, max_pw_count_;
};

#endif
