#ifndef MY_ARDUINO_H_
#define MY_ARDUINO_H_
/**************************************************************************************************
my_arduino.h

A customized library for interfacing with my Arduino UNO R3 and avr-gcc/avr-g++.

Author: Ryan Leach
**************************************************************************************************/
#include <avr/io.h>
#include "compile_time.h"

//
// Digital IO pins.
//
enum class Pins { 
    D00_RX,  // PD0
    D01_TX,  // PD1
    D02,     // PD2
    D03_PWM, // PD3, OC2B
    D04,     // PD4
    D05_PWM, // PD5, OC0B
    D06_PWM, // PD6, OC0A
    D07,     // PD7
    D08,     // PB0
    D09_PWM, // PB1, OC1A
    D10_PWM, // PB2, OC1B
    D11_PWM, // PB3, OC2A
    D12,     // PB4
    D13_LED, // PB5
    AD00,    // PC0
    AD01,    // PC1
    AD02,    // PC2
    AD03,    // PC3
    AD04,    // PC4
    AD05     // PC5
};

enum class DataDirection { IN, IN_PULL_UP, OUT };
enum class PinValue {HIGH, LOW };

inline void set_pin_mode(const Pins pin, const DataDirection direction) {
    switch(direction) {
        case DataDirection::IN: {
            switch(pin) {
                case Pins::D00_RX : CLEAR_BIT(PORTD, PD0); CLEAR_BIT(DDRD, PD0); break;
                case Pins::D01_TX : CLEAR_BIT(PORTD, PD1); CLEAR_BIT(DDRD, PD1); break;
                case Pins::D02    : CLEAR_BIT(PORTD, PD2); CLEAR_BIT(DDRD, PD2); break;
                case Pins::D03_PWM: CLEAR_BIT(PORTD, PD3); CLEAR_BIT(DDRD, PD3); break;
                case Pins::D04    : CLEAR_BIT(PORTD, PD4); CLEAR_BIT(DDRD, PD4); break;
                case Pins::D05_PWM: CLEAR_BIT(PORTD, PD5); CLEAR_BIT(DDRD, PD5); break;
                case Pins::D06_PWM: CLEAR_BIT(PORTD, PD6); CLEAR_BIT(DDRD, PD6); break;
                case Pins::D07    : CLEAR_BIT(PORTD, PD7); CLEAR_BIT(DDRD, PD7); break;

                case Pins::D08    : CLEAR_BIT(PORTB, PB0); CLEAR_BIT(DDRB, PB0); break;
                case Pins::D09_PWM: CLEAR_BIT(PORTB, PB1); CLEAR_BIT(DDRB, PB1); break;
                case Pins::D10_PWM: CLEAR_BIT(PORTB, PB2); CLEAR_BIT(DDRB, PB2); break;
                case Pins::D11_PWM: CLEAR_BIT(PORTB, PB3); CLEAR_BIT(DDRB, PB3); break;
                case Pins::D12    : CLEAR_BIT(PORTB, PB4); CLEAR_BIT(DDRB, PB4); break;
                case Pins::D13_LED: CLEAR_BIT(PORTB, PB5); CLEAR_BIT(DDRB, PB5); break;

                case Pins::AD00   : CLEAR_BIT(PORTC, PC0); CLEAR_BIT(DDRC, PC0); break;
                case Pins::AD01   : CLEAR_BIT(PORTC, PC1); CLEAR_BIT(DDRC, PC1); break;
                case Pins::AD02   : CLEAR_BIT(PORTC, PC2); CLEAR_BIT(DDRC, PC2); break;
                case Pins::AD03   : CLEAR_BIT(PORTC, PC3); CLEAR_BIT(DDRC, PC3); break;
                case Pins::AD04   : CLEAR_BIT(PORTC, PC4); CLEAR_BIT(DDRC, PC4); break;
                case Pins::AD05   : CLEAR_BIT(PORTC, PC5); CLEAR_BIT(DDRC, PC5); break;
            }
        }
        break;
        case DataDirection::IN_PULL_UP: {
            switch(pin) {
                case Pins::D00_RX : SET_BIT(PORTD, PD0); CLEAR_BIT(DDRD, PD0); break;
                case Pins::D01_TX : SET_BIT(PORTD, PD1); CLEAR_BIT(DDRD, PD1); break;
                case Pins::D02    : SET_BIT(PORTD, PD2); CLEAR_BIT(DDRD, PD2); break;
                case Pins::D03_PWM: SET_BIT(PORTD, PD3); CLEAR_BIT(DDRD, PD3); break;
                case Pins::D04    : SET_BIT(PORTD, PD4); CLEAR_BIT(DDRD, PD4); break;
                case Pins::D05_PWM: SET_BIT(PORTD, PD5); CLEAR_BIT(DDRD, PD5); break;
                case Pins::D06_PWM: SET_BIT(PORTD, PD6); CLEAR_BIT(DDRD, PD6); break;
                case Pins::D07    : SET_BIT(PORTD, PD7); CLEAR_BIT(DDRD, PD7); break;

                case Pins::D08    : SET_BIT(PORTB, PB0); CLEAR_BIT(DDRB, PB0); break;
                case Pins::D09_PWM: SET_BIT(PORTB, PB1); CLEAR_BIT(DDRB, PB1); break;
                case Pins::D10_PWM: SET_BIT(PORTB, PB2); CLEAR_BIT(DDRB, PB2); break;
                case Pins::D11_PWM: SET_BIT(PORTB, PB3); CLEAR_BIT(DDRB, PB3); break;
                case Pins::D12    : SET_BIT(PORTB, PB4); CLEAR_BIT(DDRB, PB4); break;
                case Pins::D13_LED: SET_BIT(PORTB, PB5); CLEAR_BIT(DDRB, PB5); break;

                case Pins::AD00   : SET_BIT(PORTC, PC0); CLEAR_BIT(DDRC, PC0); break;
                case Pins::AD01   : SET_BIT(PORTC, PC1); CLEAR_BIT(DDRC, PC1); break;
                case Pins::AD02   : SET_BIT(PORTC, PC2); CLEAR_BIT(DDRC, PC2); break;
                case Pins::AD03   : SET_BIT(PORTC, PC3); CLEAR_BIT(DDRC, PC3); break;
                case Pins::AD04   : SET_BIT(PORTC, PC4); CLEAR_BIT(DDRC, PC4); break;
                case Pins::AD05   : SET_BIT(PORTC, PC5); CLEAR_BIT(DDRC, PC5); break;
            }
        }
        break;
        case DataDirection::OUT: {
            switch(pin) {
                case Pins::D00_RX : SET_BIT(DDRD, PD0); CLEAR_BIT(PORTD, PD0); break;
                case Pins::D01_TX : SET_BIT(DDRD, PD1); CLEAR_BIT(PORTD, PD1); break;
                case Pins::D02    : SET_BIT(DDRD, PD2); CLEAR_BIT(PORTD, PD2); break;
                case Pins::D03_PWM: SET_BIT(DDRD, PD3); CLEAR_BIT(PORTD, PD3); break;
                case Pins::D04    : SET_BIT(DDRD, PD4); CLEAR_BIT(PORTD, PD4); break;
                case Pins::D05_PWM: SET_BIT(DDRD, PD5); CLEAR_BIT(PORTD, PD5); break;
                case Pins::D06_PWM: SET_BIT(DDRD, PD6); CLEAR_BIT(PORTD, PD6); break;
                case Pins::D07    : SET_BIT(DDRD, PD7); CLEAR_BIT(PORTD, PD7); break;
                
                case Pins::D08    : SET_BIT(DDRB, PB0); CLEAR_BIT(PORTB, PB0); break;
                case Pins::D09_PWM: SET_BIT(DDRB, PB1); CLEAR_BIT(PORTB, PB1); break;
                case Pins::D10_PWM: SET_BIT(DDRB, PB2); CLEAR_BIT(PORTB, PB2); break;
                case Pins::D11_PWM: SET_BIT(DDRB, PB3); CLEAR_BIT(PORTB, PB3); break;
                case Pins::D12    : SET_BIT(DDRB, PB4); CLEAR_BIT(PORTB, PB4); break;
                case Pins::D13_LED: SET_BIT(DDRB, PB5); CLEAR_BIT(PORTB, PB5); break;
                
                case Pins::AD00   : SET_BIT(DDRC, PC0); CLEAR_BIT(PORTC, PC0); break;
                case Pins::AD01   : SET_BIT(DDRC, PC1); CLEAR_BIT(PORTC, PC1); break;
                case Pins::AD02   : SET_BIT(DDRC, PC2); CLEAR_BIT(PORTC, PC2); break;
                case Pins::AD03   : SET_BIT(DDRC, PC3); CLEAR_BIT(PORTC, PC3); break;
                case Pins::AD04   : SET_BIT(DDRC, PC4); CLEAR_BIT(PORTC, PC4); break;
                case Pins::AD05   : SET_BIT(DDRC, PC5); CLEAR_BIT(PORTC, PC5); break;
            }
        }
        break;
    }
}

inline void set_pin_value(const Pins pin, const PinValue value) {
    switch(value){
        case PinValue::HIGH: {
            switch(pin) {
                case Pins::D00_RX : SET_BIT(PORTD, PD0); break;
                case Pins::D01_TX : SET_BIT(PORTD, PD1); break;
                case Pins::D02    : SET_BIT(PORTD, PD2); break;
                case Pins::D03_PWM: SET_BIT(PORTD, PD3); break;
                case Pins::D04    : SET_BIT(PORTD, PD4); break;
                case Pins::D05_PWM: SET_BIT(PORTD, PD5); break;
                case Pins::D06_PWM: SET_BIT(PORTD, PD6); break;
                case Pins::D07    : SET_BIT(PORTD, PD7); break;
                
                case Pins::D08    : SET_BIT(PORTB, PB0); break;
                case Pins::D09_PWM: SET_BIT(PORTB, PB1); break;
                case Pins::D10_PWM: SET_BIT(PORTB, PB2); break;
                case Pins::D11_PWM: SET_BIT(PORTB, PB3); break;
                case Pins::D12    : SET_BIT(PORTB, PB4); break;
                case Pins::D13_LED: SET_BIT(PORTB, PB5); break;
                
                case Pins::AD00   : SET_BIT(PORTC, PC0); break;
                case Pins::AD01   : SET_BIT(PORTC, PC1); break;
                case Pins::AD02   : SET_BIT(PORTC, PC2); break;
                case Pins::AD03   : SET_BIT(PORTC, PC3); break;
                case Pins::AD04   : SET_BIT(PORTC, PC4); break;
                case Pins::AD05   : SET_BIT(PORTC, PC5); break;
            }
        }
        break;

        case PinValue::LOW: {
            switch(pin) {
                case Pins::D00_RX : CLEAR_BIT(PORTD, PD0); break;
                case Pins::D01_TX : CLEAR_BIT(PORTD, PD1); break;
                case Pins::D02    : CLEAR_BIT(PORTD, PD2); break;
                case Pins::D03_PWM: CLEAR_BIT(PORTD, PD3); break;
                case Pins::D04    : CLEAR_BIT(PORTD, PD4); break;
                case Pins::D05_PWM: CLEAR_BIT(PORTD, PD5); break;
                case Pins::D06_PWM: CLEAR_BIT(PORTD, PD6); break;
                case Pins::D07    : CLEAR_BIT(PORTD, PD7); break;
                
                case Pins::D08    : CLEAR_BIT(PORTB, PB0); break;
                case Pins::D09_PWM: CLEAR_BIT(PORTB, PB1); break;
                case Pins::D10_PWM: CLEAR_BIT(PORTB, PB2); break;
                case Pins::D11_PWM: CLEAR_BIT(PORTB, PB3); break;
                case Pins::D12    : CLEAR_BIT(PORTB, PB4); break;
                case Pins::D13_LED: CLEAR_BIT(PORTB, PB5); break;
                
                case Pins::AD00   : CLEAR_BIT(PORTC, PC0); break;
                case Pins::AD01   : CLEAR_BIT(PORTC, PC1); break;
                case Pins::AD02   : CLEAR_BIT(PORTC, PC2); break;
                case Pins::AD03   : CLEAR_BIT(PORTC, PC3); break;
                case Pins::AD04   : CLEAR_BIT(PORTC, PC4); break;
                case Pins::AD05   : CLEAR_BIT(PORTC, PC5); break;
            }

        }
        break;
    }
}

inline PinValue get_pin_value(const Pins pin) {
    switch(pin) {
        case Pins::D00_RX : return IS_SET(PIND, PD0) ? PinValue::HIGH : PinValue::LOW;
        case Pins::D01_TX : return IS_SET(PIND, PD1) ? PinValue::HIGH : PinValue::LOW;
        case Pins::D02    : return IS_SET(PIND, PD2) ? PinValue::HIGH : PinValue::LOW;
        case Pins::D03_PWM: return IS_SET(PIND, PD3) ? PinValue::HIGH : PinValue::LOW;
        case Pins::D04    : return IS_SET(PIND, PD4) ? PinValue::HIGH : PinValue::LOW;
        case Pins::D05_PWM: return IS_SET(PIND, PD5) ? PinValue::HIGH : PinValue::LOW;
        case Pins::D06_PWM: return IS_SET(PIND, PD6) ? PinValue::HIGH : PinValue::LOW;
        case Pins::D07    : return IS_SET(PIND, PD7) ? PinValue::HIGH : PinValue::LOW;
        
        case Pins::D08    : return IS_SET(PINB, PB0) ? PinValue::HIGH : PinValue::LOW;
        case Pins::D09_PWM: return IS_SET(PINB, PB1) ? PinValue::HIGH : PinValue::LOW;
        case Pins::D10_PWM: return IS_SET(PINB, PB2) ? PinValue::HIGH : PinValue::LOW;
        case Pins::D11_PWM: return IS_SET(PINB, PB3) ? PinValue::HIGH : PinValue::LOW;
        case Pins::D12    : return IS_SET(PINB, PB4) ? PinValue::HIGH : PinValue::LOW;
        case Pins::D13_LED: return IS_SET(PINB, PB5) ? PinValue::HIGH : PinValue::LOW;
        
        case Pins::AD00   : return IS_SET(PINC, PC0) ? PinValue::HIGH : PinValue::LOW;
        case Pins::AD01   : return IS_SET(PINC, PC1) ? PinValue::HIGH : PinValue::LOW;
        case Pins::AD02   : return IS_SET(PINC, PC2) ? PinValue::HIGH : PinValue::LOW;
        case Pins::AD03   : return IS_SET(PINC, PC3) ? PinValue::HIGH : PinValue::LOW;
        case Pins::AD04   : return IS_SET(PINC, PC4) ? PinValue::HIGH : PinValue::LOW;
        case Pins::AD05   : return IS_SET(PINC, PC5) ? PinValue::HIGH : PinValue::LOW;
    }
}

inline bool is_pin_set(const Pins pin) {
    switch(pin) {
        case Pins::D00_RX : return IS_SET(PIND, PD0);
        case Pins::D01_TX : return IS_SET(PIND, PD1);
        case Pins::D02    : return IS_SET(PIND, PD2);
        case Pins::D03_PWM: return IS_SET(PIND, PD3);
        case Pins::D04    : return IS_SET(PIND, PD4);
        case Pins::D05_PWM: return IS_SET(PIND, PD5);
        case Pins::D06_PWM: return IS_SET(PIND, PD6);
        case Pins::D07    : return IS_SET(PIND, PD7);
        
        case Pins::D08    : return IS_SET(PINB, PB0);
        case Pins::D09_PWM: return IS_SET(PINB, PB1);
        case Pins::D10_PWM: return IS_SET(PINB, PB2);
        case Pins::D11_PWM: return IS_SET(PINB, PB3);
        case Pins::D12    : return IS_SET(PINB, PB4);
        case Pins::D13_LED: return IS_SET(PINB, PB5);
        
        case Pins::AD00   : return IS_SET(PINC, PC0);
        case Pins::AD01   : return IS_SET(PINC, PC1);
        case Pins::AD02   : return IS_SET(PINC, PC2);
        case Pins::AD03   : return IS_SET(PINC, PC3);
        case Pins::AD04   : return IS_SET(PINC, PC4);
        case Pins::AD05   : return IS_SET(PINC, PC5);
    }
}

#endif