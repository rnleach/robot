#ifndef CUSTOM_SERIAL_H_
#define CUSTOM_SERIAL_H_
/**************************************************************************************************
custom_serial.h

A customized library for input/output via the serial port with avr-gcc/avr-g++.

Author: Ryan Leach
**************************************************************************************************/
#include <avr/io.h>
#include <stdio.h>
#include "compile_time.h"

//
// Set up registers - this function is normally called by the init functions.
//
void set_baud_rate(void);

//
// Initialize serial for Binary input/output. If using ascii init functions they will call these
// for you.
//
void serial_binary_out_init(void);
void serial_binary_in_init(void);
void serial_binary_inout_init(void);

//
// Initialize serial for ASCII input/output. Initializes printf, sets stdin and stdout
//
void serial_ascii_out_init(void);
void serial_ascii_in_init(void);
void serial_ascii_inout_init(void);

//
// Send and receive binary data
//
void usart_transmit( uint8_t data);
uint8_t usart_receive(void);

//
// putchar and getchar implementations for ascii serial input and output
//
int uart_putchar(char c, FILE *stream);
int uart_getchar(FILE *stream);

#endif
