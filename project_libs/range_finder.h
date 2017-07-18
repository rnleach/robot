#ifndef RANGE_FINDER_H_
#define RANGE_FINDER_H_
/**************************************************************************************************
range_finder.h

A customized library for setting up and using the HC-SR04 ultrasound moduel with avr-gcc/avr-g++.

Author: Ryan Leach
**************************************************************************************************/
#include "my_arduino.h"

template<Pins TRIG, Pins ECHO>
class RangeFinder {
    public:
        RangeFinder();
        void measure_range();
        void flush_buffer();
        uint16_t get_range_cm();
        uint16_t get_average_range();
        uint16_t get_median_range();
    private:
        static constexpr size_t RANGE_BUFFER_SIZE = 5;
        size_t next_buffer_index;
        size_t current_buffer_index;
        uint16_t ranges[RANGE_BUFFER_SIZE];
};

// TODO: Make cpp file.
#endif