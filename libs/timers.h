#ifndef CUSTOM_PWM_H_
#define CUSTOM_PWM_H_
/**************************************************************************************************
pwm.h

A customized header only library for setting up and using PWM with avr-gcc/avr-g++.

Author: Ryan Leach
**************************************************************************************************/
#include <avr/io.h>
#include "compile_time.h"

namespace Timer0 {
    // Predefined prescaler settings for Timer0.
    enum class Prescale { None, P8, P64, P256, P1024 };

    // Modes for Timer0
    enum class Mode {
        Normal,                // TOP=0xFF
        CTC,                   // TOP=OCR0A
        PWM_Phase_Correct,     // TOP=0xFF
        PWM_Fast,              // TOP=0xFF
        //PWM_Phase_Correct_VRB, // TOP=OCR0A
        //PWM_Fast_VRB,          // TOP=OCR0A
    };

    // Compare Match behavior
    enum class CompareMatch {
        // Toggle only available on OC0A, not on OC0B. Not handled by library at this time.
        // Toggle,
        // Clear, or non-inverting
        Clear,        // Non-PWM
        NonInverting, // Fast PWM
        ClearUp,      // Phase correct PWM
        
        // Set, or inverting 
        Set,          // Non-PWM
        Inverting,    // Fast PWM
        ClearDown,    // Phase correct PWM
    };

    void init(Mode mode, Prescale prescale) {
        switch(mode) {
            case Mode::Normal:
                CLEAR_BIT(TCCR0A, WGM00);
                CLEAR_BIT(TCCR0A, WGM01);
                CLEAR_BIT(TCCR0B, WGM02);
                break;
            case Mode::CTC:
                CLEAR_BIT(TCCR0A, WGM00);
                SET_BIT(TCCR0A, WGM01);
                CLEAR_BIT(TCCR0B, WGM02);
                break;
            case Mode::PWM_Phase_Correct:
                SET_BIT(TCCR0A, WGM00);
                CLEAR_BIT(TCCR0A, WGM01);
                CLEAR_BIT(TCCR0B, WGM02);
                break;
            case Mode::PWM_Fast:
                SET_BIT(TCCR0A, WGM00);
                SET_BIT(TCCR0A, WGM01);
                CLEAR_BIT(TCCR0B, WGM02);
                break;
        }

        switch(prescale) {
            case Prescale::None:
                SET_BIT(TCCR0B, CS00);
                CLEAR_BIT(TCCR0B, CS01);
                CLEAR_BIT(TCCR0B, CS02);
                break;
            case Prescale::P8:
                CLEAR_BIT(TCCR0B, CS00);
                SET_BIT(TCCR0B, CS01);
                CLEAR_BIT(TCCR0B, CS02);
                break;
            case Prescale::P64:
                SET_BIT(TCCR0B, CS00);
                SET_BIT(TCCR0B, CS01);
                CLEAR_BIT(TCCR0B, CS02);
                break;
            case Prescale::P256:
                CLEAR_BIT(TCCR0B, CS00);
                CLEAR_BIT(TCCR0B, CS01);
                SET_BIT(TCCR0B, CS02);
                break;
            case Prescale::P1024:
                SET_BIT(TCCR0B, CS00);
                CLEAR_BIT(TCCR0B, CS01);
                SET_BIT(TCCR0B, CS02);
                break;
        }
    }

    void set_count(uint8_t new_count) {
        TCNT0 = new_count;
    }

    uint8_t get_count() {
        return TCNT0;
    }

    void set_compare_match_PD6(CompareMatch compare_match) {
        switch(compare_match) {
            case CompareMatch::Clear:
            case CompareMatch::NonInverting:
            case CompareMatch::ClearUp:
                CLEAR_BIT(TCCR0A, COM0A0);
                SET_BIT(TCCR0A, COM0A1);           
                break;
            case CompareMatch::Set:
            case CompareMatch::Inverting:
            case CompareMatch::ClearDown:
                SET_BIT(TCCR0A, COM0A0);
                SET_BIT(TCCR0A, COM0A1);  
                break;
        }
    }

    void set_compare_match_PIN06(CompareMatch compare_match) {
        set_compare_match_PD6(compare_match);
    }

    void set_OCR0A(uint8_t new_value) {
        OCR0A = new_value;
    }

    uint8_t get_OCR0A() {
        return OCR0A;
    }

    void set_duty_cycle_PD6(uint8_t duty) {
        // We have to special case this for the case of 0 duty, see last  2 paragraphs of section
        // 15.7.3 on the data sheet.
        static uint8_t old_duty = 0;

        // Turn it off for special case of 0
        if( duty == 0) CLEAR_BIT(DDRD, PD6);

        // If it was 0, turn it back on
        else if( duty != 0 && old_duty == 0) SET_BIT(DDRD, PD6);
        
        // Remember old value
        old_duty = OCR0A;

        // Set the duty
        OCR0A = duty;
    }

    void set_duty_cycle_PIN06(uint8_t duty) {
        set_duty_cycle_PD6(duty);
    }

    uint8_t get_duty_cycle_PD6() {
        return get_OCR0A();
    }

    void set_compare_match_PD5(CompareMatch compare_match) {
        switch(compare_match) {
            case CompareMatch::Clear:
            case CompareMatch::NonInverting:
            case CompareMatch::ClearUp:
                CLEAR_BIT(TCCR0A, COM0B0);
                SET_BIT(TCCR0A, COM0B1);           
                break;
            case CompareMatch::Set:
            case CompareMatch::Inverting:
            case CompareMatch::ClearDown:
                SET_BIT(TCCR0A, COM0B0);
                SET_BIT(TCCR0A, COM0B1);  
                break;
        }
    }

    void set_compare_match_PIN05(CompareMatch compare_match) {
        set_compare_match_PD5(compare_match);
    }

    void set_OCR0B(uint8_t new_value) {
        OCR0B = new_value;
    }

    uint8_t get_OCR0B() {
        return OCR0B;
    }

    void set_duty_cycle_PD5(uint8_t duty) {
        // We have to special case this for the case of 0 duty, see last  2 paragraphs of section
        // 15.7.3 on the data sheet.
        static uint8_t old_duty = 0;

        // Turn it off for special case of 0
        if( duty == 0) CLEAR_BIT(DDRD, PD5);

        // If it was 0, turn it back on
        else if( duty != 0 && old_duty == 0) SET_BIT(DDRD, PD5);
        
        // Remember old value
        old_duty = OCR0B;

        // Set the duty
        OCR0B = duty;
    }

    uint8_t get_duty_cycle_PD5() {
        return get_OCR0B();
    }

    void set_duty_cycle_PIN05(uint8_t duty) {
        set_duty_cycle_PD5(duty);
    }
}

namespace Timer2 {
    // Predefined prescaler settings for Timer2.
    enum class Prescale { None, P8, P32, P64 };

    // Modes for Timer0
    enum class Mode {
        Normal,                // TOP=0xFF
        CTC,                   // TOP=OCR0A
        PWM_Phase_Correct,     // TOP=0xFF
        PWM_Fast,              // TOP=0xFF
        //PWM_Phase_Correct_VRB, // TOP=OCR2A
        //PWM_Fast_VRB,          // TOP=OCR2A
    };

    // Compare Match behavior
    enum class CompareMatch {
        // Toggle only available on OC0A, not on OC0B. Not handled by library at this time.
        // Toggle,
        // Clear, or non-inverting
        Clear,        // Non-PWM
        NonInverting, // Fast PWM
        ClearUp,      // Phase correct PWM
        
        // Set, or inverting 
        Set,          // Non-PWM
        Inverting,    // Fast PWM
        ClearDown,    // Phase correct PWM
    };

    void init(Mode mode, Prescale prescale) {
        switch(mode) {
            case Mode::Normal:
                CLEAR_BIT(TCCR2A, WGM20);
                CLEAR_BIT(TCCR2A, WGM21);
                CLEAR_BIT(TCCR2B, WGM22);
                break;
            case Mode::CTC:
                CLEAR_BIT(TCCR2A, WGM20);
                SET_BIT(TCCR2A, WGM21);
                CLEAR_BIT(TCCR2B, WGM22);
                break;
            case Mode::PWM_Phase_Correct:
                SET_BIT(TCCR2A, WGM20);
                CLEAR_BIT(TCCR2A, WGM21);
                CLEAR_BIT(TCCR2B, WGM22);
                break;
            case Mode::PWM_Fast:
                SET_BIT(TCCR2A, WGM20);
                SET_BIT(TCCR2A, WGM21);
                CLEAR_BIT(TCCR2B, WGM22);
                break;
        }

        switch(prescale) {
            case Prescale::None:
                SET_BIT(TCCR2B, CS20);
                CLEAR_BIT(TCCR2B, CS21);
                CLEAR_BIT(TCCR2B, CS22);
                break;
            case Prescale::P8:
                CLEAR_BIT(TCCR2B, CS20);
                SET_BIT(TCCR2B, CS21);
                CLEAR_BIT(TCCR2B, CS22);
                break;
            case Prescale::P32:
                SET_BIT(TCCR2B, CS20);
                SET_BIT(TCCR2B, CS21);
                CLEAR_BIT(TCCR2B, CS22);
                break;
            case Prescale::P64:
                CLEAR_BIT(TCCR2B, CS20);
                CLEAR_BIT(TCCR2B, CS21);
                SET_BIT(TCCR2B, CS22);
                break;
        }
    }

    void set_count(uint8_t new_count) {
        TCNT2 = new_count;
    }

    uint8_t get_count() {
        return TCNT2;
    }

    void set_compare_match_PB3(CompareMatch compare_match) {
        switch(compare_match) {
            case CompareMatch::Clear:
            case CompareMatch::NonInverting:
            case CompareMatch::ClearUp:
                CLEAR_BIT(TCCR2A, COM2A0);
                SET_BIT(TCCR2A, COM2A1);           
                break;
            case CompareMatch::Set:
            case CompareMatch::Inverting:
            case CompareMatch::ClearDown:
                SET_BIT(TCCR2A, COM2A0);
                SET_BIT(TCCR2A, COM2A1);  
                break;
        }
    }

    void set_compare_match_PIN11(CompareMatch compare_match) {
        set_compare_match_PB3(compare_match);
    }

    void set_OCR2A(uint8_t new_value) {
        OCR2A = new_value;
    }

    uint8_t get_OCR2A() {
        return OCR2A;
    }

    void set_duty_cycle_PB3(uint8_t duty) {
        // We have to special case this for the case of 0 duty, see last  2 paragraphs of section
        // 18.7.3 on the data sheet.
        static uint8_t old_duty = 0;

        // Turn it off for special case of 0
        if( duty == 0) CLEAR_BIT(DDRB, PB3);

        // If it was 0, turn it back on
        else if( duty != 0 && old_duty == 0) SET_BIT(DDRB, PB3);
        
        // Remember old value
        old_duty = OCR2A;

        // Set the duty
        OCR2A = duty;
    }

    void set_duty_cycle_PIN11(uint8_t duty) {
        set_duty_cycle_PB3(duty);
    }

    uint8_t get_duty_cycle_PB3() {
        return get_OCR2A();
    }

    void set_compare_match_PD3(CompareMatch compare_match) {
        switch(compare_match) {
            case CompareMatch::Clear:
            case CompareMatch::NonInverting:
            case CompareMatch::ClearUp:
                CLEAR_BIT(TCCR2A, COM2B0);
                SET_BIT(TCCR2A, COM2B1);           
                break;
            case CompareMatch::Set:
            case CompareMatch::Inverting:
            case CompareMatch::ClearDown:
                SET_BIT(TCCR2A, COM2B0);
                SET_BIT(TCCR2A, COM2B1);  
                break;
        }
    }

    void set_compare_match_PIN03(CompareMatch compare_match) {
        set_compare_match_PD3(compare_match);
    }

    void set_OCR2B(uint8_t new_value) {
        OCR2B = new_value;
    }

    uint8_t get_OCR2B() {
        return OCR2B;
    }

    void set_duty_cycle_PD3(uint8_t duty) {
        // We have to special case this for the case of 0 duty, see last  2 paragraphs of section
        // 18.7.3 on the data sheet.
        static uint8_t old_duty = 0;

        // Turn it off for special case of 0
        if( duty == 0) CLEAR_BIT(DDRD, PD3);

        // If it was 0, turn it back on
        else if( duty != 0 && old_duty == 0) SET_BIT(DDRD, PD3);
        
        // Remember old value
        old_duty = OCR2B;

        // Set the duty
        OCR2B = duty;
    }

    uint8_t get_duty_cycle_PD3() {
        return get_OCR2B();
    }

    void set_duty_cycle_PIN03(uint8_t duty) {
        set_duty_cycle_PD3(duty);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void fast_pwm_init_timer1_8bit(void)
{
    //
    // Set up the Timer/Counter Control Registers for TIMER1
    //

    // Set the prescaler to no prescaling.
    TCCR1B |= (1 << CS10);

    // Set for fast PWM 8-bit
    TCCR1A |= (1 << WGM10);
    TCCR1B |= (1<< WGM12);

    // Set for non-inverted mode on both the A and B outputs.
    TCCR1A |= (1<<COM1A1) | (1 << COM1B1); 
}

//
// PWM on PB1 pin, PIN09 on the arduino board
//

void fast_pwm_init_8bit_PB1(void)
{
    // This one uses TIMER1, make sure to call fast_pwm_init_timer1_8bit()

    // Set up output.
    DDRB |= (1<<PB1);

    // Initialize to 0% duty cycle
    OCR1A = 0;
}

void set_duty_cycle_8bit_PB1(uint8_t duty)
{
    OCR1A = duty;
}

void set_duty_cycle_8bit_percent_PB1(float percent)
{
    set_duty_cycle_8bit_PB1((int8_t)(255 * percent));
}

//
// PWM on PB2 pin, PIN10 on the arduino board
//

void fast_pwm_init_8bit_PB2(void)
{
    // This one uses TIMER1, make sure to call fast_pwm_init_timer1_8bit()

    // Set up output.
    DDRB |= (1<<PB2);

    // Initialize to 0% duty cycle
    OCR1B = 0;
}

void set_duty_cycle_8bit_PB2(uint8_t duty)
{
    OCR1B = duty;
}

void set_duty_cycle_8bit_percent_PB2(float percent)
{
    set_duty_cycle_8bit_PB2((int8_t)(255 * percent));
}

#endif