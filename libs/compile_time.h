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

// Set and clear bits in a register. (Same code works on any variable.)
#define SET_BIT(register, bit) ((register) |= (1<<(bit)))
#define CLEAR_BIT(register, bit) ((register) &= ~(1<<(bit)))

// Check if a bit is set or cleared in a register. (Same code works on any variable.)
#define IS_SET(register, bit) ((register) & (1<<(bit)))

// Constant for the processor clock speed, should be overridden with -D CFLAG in the makefile.
#ifndef F_CPU
#   define F_CPU 16000000UL
#   pragma message "\n\n     WARNING: DEFAULT F_CPU OF " STRINGIFY(F_CPU) " USED FOR CRYSTAL\n" \
                       "     FREQUENCY. OVERRIDE WITH COMPILER OPTION IF NEEDED.\n\n"
#endif

#endif
