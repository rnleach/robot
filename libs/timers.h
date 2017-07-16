#ifndef TIMERS_H_
#define TIMERS_H_
/**************************************************************************************************
timers.h

A customized library for setting up and using timers with avr-gcc/avr-g++.

Author: Ryan Leach
**************************************************************************************************/
#include <avr/io.h>
#include <util/atomic.h>
#include "compile_time.h"

namespace Timer0 {
    // Predefined prescaler settings for Timer0.
    enum class Prescale { None = 1, P8 = 8, P64 = 64, P256 = 256, P1024 = 1024 };

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

    // Timer specific (applies to both channels A and B)
    void set_mode(Mode mode);
    void set_prescale(Prescale prescale);
    void set_count(uint8_t new_count);
    uint8_t get_count();
    // TODO: Add set_frequency, which will only work in CTC mode, until the other modes are added.

    // Channel A
    void set_compare_match_Ch_A(CompareMatch compare_match);
    void set_compare_match_PD6(CompareMatch compare_match);
    void set_compare_match_PIN06(CompareMatch compare_match);
    void set_OCR0A(uint8_t new_value);
    uint8_t get_OCR0A();
    void set_duty_cycle_Ch_A(uint8_t duty);
    void set_duty_cycle_PD6(uint8_t duty);
    void set_duty_cycle_PIN06(uint8_t duty);
    uint8_t get_duty_cycle_Ch_A();
    uint8_t get_duty_cycle_PD6();
    uint8_t get_duty_cycle_PIN06();

    // Channel B
    void set_compare_match_Ch_B(CompareMatch compare_match);
    void set_compare_match_PD5(CompareMatch compare_match);
    void set_compare_match_PIN05(CompareMatch compare_match);
    void set_OCR0B(uint8_t new_value);
    uint8_t get_OCR0B();
    void set_duty_cycle_Ch_B(uint8_t duty);
    void set_duty_cycle_PD5(uint8_t duty);
    void set_duty_cycle_PIN05(uint8_t duty);
    uint8_t get_duty_cycle_Ch_B();
    uint8_t get_duty_cycle_PD5();
    uint8_t get_duty_cycle_PIN05();
}

namespace Timer1 {
    
    enum class Prescale { None = 1, P8 = 8, P64 = 64, P256 = 256, P1024 = 1024 };

    enum class Mode {
        Off,                        // Timer not running.
        Normal,                     // Just a counter, time
        PhaseCorrectPWM08,          // 8-bit, TOP = 0x00FF
        PhaseCorrectPWM09,          // 9-bit, TOP = 0x01FF
        PhaseCorrectPWM10,          // 10-bit, TOP = 0x03FF
        CTC,                        // TOP = OCR1A
        FastPWM08,                  // 8-bit, TOP = 0x00FF
        FastPWM09,                  // 9-bit, TOP = 0x01FF
        FastPWM10,                  // 10-bit, TOP = 0x03FF
        PhaseFreqCorrect_InputTop,  // TOP = ICR1
        PhaseFreqCorrect_OutputTop, // TOP = OCR1A
        PhaseCorrect_InputTop,      // TOP = ICR1
        PhaseCorrect_OutputTop,     // TOP = OCR1A
        CTC_InputTop,               // TOP = ICR1
        FastPWM_InputTop,           // TOP = ICR1
        FastPWM_OutputTop,          // TOP = OCR1A
    };

    // Compare Match behavior
    enum class CompareMatch {
        // Toggle options are many depending on other settings AND modes.
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

    // Timer specific (applies to both channels A and B)
    void set_mode(Mode mode);
    Mode get_mode();
    bool is_on();
    void set_prescaler(Prescale newPrescale);
    uint8_t get_prescale();
    uint16_t get_max();
    uint16_t get_top();
    void set_top(uint16_t newTop);
    void set_frequency(uint16_t hertz);
    void set_count(uint16_t new_count);
    uint16_t get_count();

    // Channel A
    void set_OCR1A(uint16_t newValue);
    uint16_t get_OCR1A();
    void set_duty_cycle_Ch_A(uint16_t newDuty);
    void set_duty_cycle_PB1(uint16_t newDuty);
    void set_duty_cycle_PIN09(uint16_t newDuty);
    uint16_t get_duty_cycle_Ch_A();
    uint16_t get_duty_cycle_PB1();
    uint16_t get_duty_cycle_PIN09();
    void set_compare_match_Ch_A(CompareMatch compareMatch);
    void set_compare_match_PB1(CompareMatch compareMatch);
    void set_compare_match_PIN09(CompareMatch compareMatch);

    // Channel B
    void set_OCR1B(uint16_t newValue);
    uint16_t get_OCR1B();
    void set_duty_cycle_Ch_B(uint16_t newDuty);
    void set_duty_cycle_PB2(uint16_t newDuty);
    void set_duty_cycle_PIN10(uint16_t newDuty);
    uint16_t get_duty_cycle_Ch_B();
    uint16_t get_duty_cycle_PB2();
    uint16_t get_duty_cycle_PIN10();
    void set_compare_match_Ch_B(CompareMatch compareMatch);
    void set_compare_match_PB2(CompareMatch compareMatch);
    void set_compare_match_PIN10(CompareMatch compareMatch);
};

namespace Timer2 {
    // Predefined prescaler settings for Timer2.
    enum class Prescale { None = 1, P8 = 8, P32 = 32, P64 = 64 };

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
        // Toggle only available on OC2A, not on OC2B. Not handled by library at this time.
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

    // Timer specific (applies to both channels A and B)
    void set_mode(Mode mode);
    void set_prescale(Prescale prescale);
    void set_count(uint8_t new_count);
    uint8_t get_count();
    // TODO: Add set_frequency, which will only work in CTC mode, until the other modes are added.

    // Channel A
    void set_compare_match_Ch_A(CompareMatch compare_match);
    void set_compare_match_PB3(CompareMatch compare_match);
    void set_compare_match_PIN11(CompareMatch compare_match);
    void set_OCR2A(uint8_t new_value);
    uint8_t get_OCR2A();
    void set_duty_cycle_Ch_A(uint8_t duty);
    void set_duty_cycle_PB3(uint8_t duty);
    void set_duty_cycle_PIN11(uint8_t duty);
    uint8_t get_duty_cycle_Ch_A();
    uint8_t get_duty_cycle_PB3();
    uint8_t get_duty_cycle_PIN11();

    // Channel B
    void set_compare_match_Ch_B(CompareMatch compare_match);
    void set_compare_match_PD3(CompareMatch compare_match);
    void set_compare_match_PIN03(CompareMatch compare_match);
    void set_OCR2B(uint8_t new_value);
    uint8_t get_OCR2B();
    void set_duty_cycle_Ch_B(uint8_t duty);
    void set_duty_cycle_PD3(uint8_t duty);
    void set_duty_cycle_PIN03(uint8_t duty);
    uint8_t get_duty_cycle_Ch_B();
    uint8_t get_duty_cycle_PD3();
    uint8_t get_duty_cycle_PIN03();
}

#endif