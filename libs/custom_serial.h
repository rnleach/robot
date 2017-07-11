#ifndef CUSTOM_SERIAL_H_
#define CUSTOM_SERIAL_H_
/**************************************************************************************************
custom_serial.h

A customized header only library for input/output via the serial port with avr-gcc/avr-g++.

Author: Ryan Leach
**************************************************************************************************/

// FIXME: Break this into a header and a cpp file.

#include <avr/io.h>
#include <stdio.h>
#include "compile_time.h"

// Constant for the BAUD rate, define in make file with -D CFLAG.
#ifndef BAUD
#   define BAUD 9600
#   pragma message "\n\n     WARNING: DEFAULT BAUD OF " STRINGIFY(BAUD) " USED FOR BAUD\n" \
                       "     RATE. OVERRIDE WITH COMPILER OPTION IF NEEDED.\n\n"
#endif

#if BAUD == 115200 && F_CPU == 16000000UL
#  define CALC_UBRR 8
#elif BAUD == 76800 && F_CPU == 16000000UL
#  define CALC_UBRR 12
#elif BAUD == 57600 && F_CPU == 16000000UL
#  define CALC_UBRR 16
#elif BAUD == 38400 && F_CPU == 16000000UL
#  define CALC_UBRR 25
#elif BAUD == 28800 && F_CPU == 16000000UL
#  define CALC_UBRR 34
#elif BAUD == 19200 && F_CPU == 16000000UL
#  define CALC_UBRR 51
#elif BAUD == 14400 && F_CPU == 16000000UL
#  define CALC_UBRR 68
#elif BAUD == 9600 && F_CPU == 16000000UL
#  define CALC_UBRR 103
#elif BAUD == 4800 && F_CPU == 16000000UL
#  define CALC_UBRR 207
#elif BAUD == 2400 && F_CPU == 16000000UL
#  define CALC_UBRR 416
#elif BAUD == 1200 && F_CPU == 16000000UL
#  define CALC_UBRR 832
#elif BAUD == 600 && F_CPU == 16000000UL
#  define CALC_UBRR 1666
#elif BAUD == 300 && F_CPU == 16000000UL
#  define CALC_UBRR 3332
#else
   // Have to be careful here, experimentation shows this requires rounding, not truncation.
   // Hence the checks for common values above. 
#  define CALC_UBRR ((F_CPU / 16 / BAUD) - 1)
#  pragma message "\n\n\nWARNING: USING CALCULATED UBRR FOR SERIAL BAUD RATE - MAY FAIL.\n\n\n"
#endif

#pragma message("\n\n          F_CPU defined as => " STRINGIFY(F_CPU) \
                  "\n          and BAUD rate defined as => " STRINGIFY(BAUD) \
                  "\n          and the CALC_UBRR value is => " STRINGIFY(CALC_UBRR) \
               "\n\n")

//
// Initialize serial for ASCII input/output. Initializes printf, sets stdin and stdout
//
void serial_ascii_out_init(void);
void serial_ascii_in_init(void);
void serial_ascii_inout_init(void);

//
// Initialize serial for Binary input/output. 
//
void serial_binary_out_init(void);
void serial_binary_in_init(void);
void serial_binary_inout_init(void);

//
// send binary data down the serial line
//
void usart_transmit( uint8_t data)
{
    // Wait for empty transmit buffer
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = data;
}

//
// receive binary data on the serial line
//
uint8_t usart_receive(void)
{
    while( !(UCSR0A & (1<<RXC0)) );
    return(UDR0);
}

//
// putchar and getchar implementations for ascii serial input and output
//
int uart_putchar(char c, FILE *stream)
{
    if (c == '\n') uart_putchar('\r', stream);
    usart_transmit(c);

    return 0;
}

int uart_getchar(FILE *stream)
{
    return usart_receive();
}

//
// Set up registers
//
void set_baud_rate(void)
{
    // Set the baud rate
    UBRR0H = (uint8_t)(CALC_UBRR >> 8);
    UBRR0L = (uint8_t) CALC_UBRR;
}

// Implementations
void serial_binary_out_init(void)
{
    set_baud_rate();

    // Enable transmit
    UCSR0B = (1<<TXEN0);
}

void serial_binary_in_init(void)
{
    set_baud_rate();

    // Enable receive
    UCSR0B = (1<<RXEN0);
}

void serial_binary_inout_init(void)
{
    set_baud_rate();

    // Enable receive and transmit
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
}

void serial_ascii_out_init(void)
{
    serial_binary_out_init();

    // send stdout to serial
    stdout = fdevopen(uart_putchar, NULL);
}

void serial_ascii_in_init(void)
{
    serial_binary_in_init();
    
    // redirect serial_in to stdin
    stdin = fdevopen(NULL, uart_getchar);
}

void serial_ascii_inout_init(void)
{
    serial_binary_inout_init();

    // redirect stdin and stdout
    FILE *serial_inout = fdevopen(uart_putchar, uart_getchar);
    stdout = serial_inout;
    stdin = serial_inout;
}

#endif
