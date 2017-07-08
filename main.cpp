#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "timers.h"

void init (void)
{
    // Set PIN12/PB4 as an output
    DDRB |= (1<<PIN4);

    // Start with LED on
    PORTB |= (1<<PORTB4);
}

int main (void)
{
    init();

        for(uint16_t i = 0; i < 6000; ++i)
        {
            PORTB |= (1<<PORTB4);
            _delay_ms(10000);
            PORTB &= ~(1<<PORTB4);
        }
        for(uint16_t i = 0; i < 6000; ++i)
        {
            PORTB |= (1<<PORTB4);
            _delay_ms(10);
            PORTB &= ~(1<<PORTB4);
        }
        
}
