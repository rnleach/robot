#ifndef TIMER_H_
#define TIMER_H_
/**************************************************************************************************
timer.h

A customized library for setting up and using timers with avr-gcc/avr-g++.
**************************************************************************************************/
#include <avr/io.h>
#include <util/atomic.h>
#include "compile_time.h"

//
// General timer template, non instantiateable. Use specialized versions only!
//
template<uint8_t N>
class Timer {
    static_assert(N <= 2, "Timer<N> does not exist! only Timer<0>, Timer<1>, and Time<2> exist.");
};

//
// Timer0
//
template<>
class Timer<0> {

    public:

        // Predefined prescaler settings for Timer0.
        enum class Prescale { None = 1, P8 = 8, P64 = 64, P256 = 256, P1024 = 1024 };

        // Modes for Timer0
        enum class Mode {
            Off,                   // Timer not running
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
        static void set_mode(Mode mode) {
            // If not off, ensure we set the prescaler, since it is used to turn the timer on/off
            if(mode != Mode::Off) set_prescaler(currentPrescale_);

            switch(mode) {
                case Mode::Off:
                    CLEAR_BIT(TCCR0B, CS00);
                    CLEAR_BIT(TCCR0B, CS01);
                    CLEAR_BIT(TCCR0B, CS02);
                    // Fall through to normal just to reset all these bits to zero like they would be
                    // on a cold start.
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
            currentMode_ = mode;
        }

        static Mode get_mode() {
            return currentMode_;
        }

        static bool is_on() {
            return currentMode_ != Mode::Off;
        }

        static void set_prescaler(Prescale prescale) {
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

            currentPrescale_ = prescale;
        }

        static uint8_t get_prescale() {
            return static_cast<uint8_t>(currentPrescale_);
        }

        static uint8_t get_max() {
            return 0xFF;
        }
        
        // static uint16_t get_top();      // TODO:
        // static void set_top(uint16_t newTop);   // TODO:
        // static void set_frequency(uint16_t hertz);  // TODO:
        // static void set_count(uint16_t new_count);  // TODO:
        // static uint16_t get_count();  // TODO:

    private:
        static Mode currentMode_;
        static Prescale currentPrescale_;

};
Timer<0>::Mode Timer<0>::currentMode_ = Timer<0>::Mode::Off;
Timer<0>::Prescale Timer<0>::currentPrescale_ = Timer<0>::Prescale::None;

#endif