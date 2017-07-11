#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>

#include "timers.h"
#include "compile_time.h"
#include "custom_serial.h"

void init (void)
{
    serial_ascii_inout_init();
    // Set PIN09/PB1 as an output
    SET_BIT(DDRB, PB1);

    Timer1::set_mode(Timer1::Mode::FastPWM_InputTop);
    Timer1::set_prescaler(Timer1::Prescale::P8);
    Timer1::set_compare_match_PIN09(Timer1::CompareMatch::NonInverting); // PB1
    Timer1::set_frequency(50);
    Timer1::set_OCR1A(3390);
}

int main (void)
{
    init();
    while(1){
        printf("MAX      = %u\n", Timer1::get_max());
        printf("TOP      = %u\n", Timer1::get_top());
        printf("PRESCALE = %u\n", Timer1::get_prescale());
        
        #define MAXT 5100
        #define MINT 1480
        #define DELAY 1000

        _delay_ms(DELAY);
        Timer1::set_OCR1A(MAXT);
        printf("OCR1A    = %u\n", Timer1::get_OCR1A());
        
        _delay_ms(DELAY);
        Timer1::set_OCR1A((MAXT + MINT) /2);
        printf("OCR1A    = %u\n", Timer1::get_OCR1A());
        
        _delay_ms(DELAY);
        Timer1::set_OCR1A(MINT);
        printf("OCR1A    = %u\n", Timer1::get_OCR1A());

        _delay_ms(DELAY);
        Timer1::set_OCR1A((MAXT + MINT) /2);
        printf("OCR1A    = %u\n", Timer1::get_OCR1A());

        uint16_t integer = 0;
        printf("Enter an integer: ");
        scanf("%lu", &integer);
        printf ("\nYou have entered %#x (%u).\n\n",integer,integer);

        Timer1::set_OCR1A(integer);
        printf("OCR1A    = %u\n\n", Timer1::get_OCR1A());
    }
        
}
