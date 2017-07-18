#ifndef ROBOT_SERVO_H_
#define ROBOT_SERVO_H_
/**************************************************************************************************
servo.h

A customized project library for managing servos..

Author: Ryan Leach
**************************************************************************************************/
// #include <avr/io.h>
// #include <util/delay.h>
#include <stdint.h>
// #include <stdio.h>

// TODO: templatize this to work with pins
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
