#include "custom_serial.h"

// Constant for the BAUD rate, define in make file with -D CFLAG.
#ifndef BAUD
#   define BAUD 9600
#   pragma message "\n\n     WARNING: DEFAULT BAUD OF " STRINGIFY(BAUD) " USED FOR BAUD\n" \
                       "     RATE. OVERRIDE WITH COMPILER OPTION IF NEEDED.\n\n"
#endif

#include <util/setbaud.h>
#define CALC_UBRR UBRR_VALUE

// Disable 2X speed for now.
#if USE_2X
#   error "USE_2X restricted."
#endif

#pragma message("\n\n          F_CPU defined as => " STRINGIFY(F_CPU) \
                  "\n          and BAUD rate defined as => " STRINGIFY(BAUD) \
                  "\n          and the CALC_UBRR value is => " STRINGIFY(CALC_UBRR) \
               "\n\n")

void set_baud_rate(void)
{
    UBRR0H = (uint8_t)(CALC_UBRR >> 8);
    UBRR0L = (uint8_t) CALC_UBRR;
}

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

    stdout = fdevopen(uart_putchar, NULL);
}

void serial_ascii_in_init(void)
{
    serial_binary_in_init();
    
    stdin = fdevopen(NULL, uart_getchar);
}

void serial_ascii_inout_init(void)
{
    serial_binary_inout_init();

    FILE *serial_inout = fdevopen(uart_putchar, uart_getchar);
    stdout = serial_inout;
    stdin = serial_inout;
}

void usart_transmit( uint8_t data)
{
    // Wait for empty transmit buffer
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = data;
}

uint8_t usart_receive(void)
{
    while( !(UCSR0A & (1<<RXC0)) );
    return(UDR0);
}

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
