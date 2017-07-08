#ifndef COMPILE_TIME_H_
#define COMPILE_TIME_H_
/**************************************************************************************************
compile_time.h

A customized header only library for compile time messaging and diagnostics with avr-gcc/avr-g++.

Author: Ryan Leach
**************************************************************************************************/

// Macros to make evaluate a #DEFINE'd variable to its value and create a string from that.
#define STRINGIFY(s) STRINGIFY_(s)
#define STRINGIFY_(s) #s

// #define TEST_VALUE 0XAF
// #pragma message ("\n\nput message here " STRINGIFY(TEST_VALUE))
// #pragma message ("\n\nput message here " STRINGIFY(_CUSTOM_SERIAL_H_))

// Set and clear bits in a register.
#define SET_BIT(register, bit) ((register) |= (1<<(bit)))
#define CLEAR_BIT(register, bit) ((register) &= ~(1<<(bit)))

#endif
