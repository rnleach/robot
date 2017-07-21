#ifndef TIMER_H_
#define TIMER_H_
/**************************************************************************************************
timer.h

A customized library for setting up and using timers with avr-gcc/avr-g++.
**************************************************************************************************/
#include <avr/io.h>
#include <util/atomic.h>
#include "compile_time.h"
#include "my_arduino.h"

//
// Valid timers - used to parameterize templates
//
enum class Timers {T0, T1, T2 };

//
// Size of counter register and output compare registers
//
template <Timers T> struct TimerValueType { using ValueType = uint8_t; };
template<> struct TimerValueType<Timers::T1> { using ValueType = uint16_t; };

//
// Available prescaler settings
//
template<Timers TN>
struct PrescalerT { 
    using PType = enum class Prescale { None = 1, P8 = 8, P64 = 64, P256 = 256, P1024 = 1024 };
};

template<>
struct PrescalerT<Timers::T2> { 
    using PType = enum class Prescale { None = 1, P8 = 8, P32 = 32, P64 = 64 };
};

//
// Modes
//
template<Timers TN>
struct ModesT {
    using MType = enum class Mode {
        Off,                   // Timer not running.
        Normal,                // TOP=0xFF
        CTC,                   // TOP=OCRnA
        PWM_Phase_Correct,     // TOP=0xFF
        PWM_Fast,              // TOP=0xFF
        //PWM_Phase_Correct_VRB, // TOP=OCRnA
        //PWM_Fast_VRB,          // TOP=OCRnA
    };
};

template<>
struct ModesT<Timers::T1> {
    using MType = enum class Mode {
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
};

//
// Compare Match behavior
//
template<Timers TN>
struct CompareMatchT {
    using CType = enum class CompareMatch {
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
};

//
// Common Registers 
//
template<Timers TN>
struct Registers {
    static volatile typename TimerValueType<TN>::ValueType& tcnt;
    static volatile typename TimerValueType<TN>::ValueType& ocrna;
    static volatile typename TimerValueType<TN>::ValueType& ocrnb;
    static volatile uint8_t& tccrna;
    static volatile uint8_t& tccrnb;
};

//
// Common interface
//
template<Timers TN>
class Timer {
    public:
        // Timer specific - applies to both channels
        static void set_mode(typename ModesT<TN>::MType mode);
        static typename ModesT<TN>::MType get_mode();
        static bool is_on();
        static void set_prescaler(typename PrescalerT<TN>::PType newPrescale);
        static uint16_t get_prescale();
        // Update currentMode_, currentPrescale_ in case something else changed them
        // TODO: static void check_state(); 
        static typename TimerValueType<TN>::ValueType get_max();
        static typename TimerValueType<TN>::ValueType get_top();
        static void set_top(typename TimerValueType<TN>::ValueType newTop);
        static void set_frequency(uint16_t hertz);
        static void set_count(typename TimerValueType<TN>::ValueType new_count);
        static typename TimerValueType<TN>::ValueType get_count();

        // Channel A
        // TODO:
        static void set_ocrna(typename TimerValueType<TN>::ValueType newValue);
        // TODO:
        static void set_compare_match_Ch_A(typename CompareMatchT<TN>::CType compareMatch);
        // TODO:
        static typename TimerValueType<TN>::ValueType get_ocrna();

        // Channel B
        static void set_ocrnb(typename TimerValueType<TN>::ValueType newValue);
        // TODO:
        static void set_compare_match_Ch_B(typename CompareMatchT<TN>::CType compareMatch);
        // TODO:
        static typename TimerValueType<TN>::ValueType get_ocrnb();
        
        // Call for each output pin
        // TODO:
        template<Pins P>
        void set_duty_cycle(typename TimerValueType<TN>::ValueType newDuty);

        // TODO:
        template<Pins P>
        typename TimerValueType<TN>::ValueType get_duty_cycle();
        
    private:
        static typename PrescalerT<TN>::PType currentPrescale_;
        static typename ModesT<TN>::MType currentMode_;
};

template<Timers TN>
typename PrescalerT<TN>::PType Timer<TN>::currentPrescale_ = PrescalerT<TN>::PType::None;

template<Timers TN>
typename ModesT<TN>::MType Timer<TN>::currentMode_ = ModesT<TN>::MType::Off;

//
// Implementations ---------------------------------------------------------------------------------
//

template<> void Timer<Timers::T0>::set_prescaler(typename PrescalerT<Timers::T0>::PType prescale);
template<> void Timer<Timers::T1>::set_prescaler(typename PrescalerT<Timers::T1>::PType newPrescale);
template<> void Timer<Timers::T2>::set_prescaler(typename PrescalerT<Timers::T2>::PType prescale);

template<Timers TN>
uint16_t Timer<TN>::get_prescale() {
    return static_cast<uint16_t>(currentPrescale_);
}

template<> void Timer<Timers::T0>::set_mode(typename ModesT<Timers::T0>::MType mode);
template<> void Timer<Timers::T1>::set_mode(typename ModesT<Timers::T1>::MType mode);
template<> void Timer<Timers::T2>::set_mode(typename ModesT<Timers::T2>::MType mode);

template<Timers TN>
auto Timer<TN>::get_mode() -> typename ModesT<TN>::MType {
    return currentMode_;
}

template<Timers TN>
bool Timer<TN>::is_on() {
    using Mode = typename ModesT<TN>::MType;

    return currentMode_ != Mode::Off;
}

template<Timers TN>
typename TimerValueType<TN>::ValueType Timer<TN>::get_max() {
    return 0xFF;
}

template<> typename TimerValueType<Timers::T1>::ValueType Timer<Timers::T1>::get_max();

template<Timers TN>
typename TimerValueType<TN>::ValueType Timer<TN>::get_top() {
    using Mode = typename ModesT<TN>::MType;
    switch(currentMode_){
        case Mode::Off:
        case Mode::Normal:
        case Mode::PWM_Phase_Correct:
        case Mode::PWM_Fast:
            return 0xFF;
        case Mode::CTC:
            return Registers<TN>::ocrna;
    }
}

template<> typename TimerValueType<Timers::T1>::ValueType Timer<Timers::T1>::get_top();

template<Timers TN>
void Timer<TN>::set_top(typename TimerValueType<TN>::ValueType new_top) {
    using Mode = typename ModesT<TN>::MType;
    switch(currentMode_){
        case Mode::Off:
        case Mode::Normal:
        case Mode::PWM_Phase_Correct:
        case Mode::PWM_Fast:
            // No op, Top is fixed. Just ignore it.
            break;
        case Mode::CTC:
            Registers<TN>::ocrna = new_top;
    }
}

template<> void Timer<Timers::T1>::set_top(typename TimerValueType<Timers::T1>::ValueType new_top);
template<> void Timer<Timers::T1>::set_frequency(uint16_t hertz);

template<Timers TN>
auto Timer<TN>::get_count() -> typename TimerValueType<TN>::ValueType {
    return Registers<TN>::tcnt;
}

template<> auto Timer<Timers::T1>::get_count() -> TimerValueType<Timers::T1>::ValueType;

template<Timers TN>
void Timer<TN>::set_count(typename TimerValueType<TN>::ValueType new_count) {
    Registers<TN>::tcnt = new_count;
}

template<> 
void Timer<Timers::T1>::set_count(typename TimerValueType<Timers::T1>::ValueType new_count);

#endif