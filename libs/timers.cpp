#include "timers.h"

namespace Timer0 {

    void set_mode(Mode mode) {
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
    }

    void set_prescaler(Prescale prescale) {
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

    void set_compare_match_Ch_A(CompareMatch compare_match) {
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

    void set_compare_match_PD6(CompareMatch compare_match) {
        set_compare_match_Ch_A(compare_match);
    }

    void set_compare_match_PIN06(CompareMatch compare_match) {
        set_compare_match_Ch_A(compare_match);
    }

    void set_OCR0A(uint8_t new_value) {
        OCR0A = new_value;
    }

    uint8_t get_OCR0A() {
        return OCR0A;
    }

    void set_duty_cycle_Ch_A(uint8_t duty) {
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

    void set_duty_cycle_PD6(uint8_t duty) {
        set_duty_cycle_Ch_A(duty);
    }

    void set_duty_cycle_PIN06(uint8_t duty) {
        set_duty_cycle_Ch_A(duty);
    }

    uint8_t get_duty_cycle_Ch_A(){
        return get_OCR0A();
    }

    uint8_t get_duty_cycle_PD6(){
        return get_OCR0A();
    }

    uint8_t get_duty_cycle_PIN06(){
        return get_OCR0A();
    }

    void set_compare_match_Ch_B(CompareMatch compare_match) {
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

    void set_compare_match_PD5(CompareMatch compare_match) {
        set_compare_match_Ch_B(compare_match);
    }

    void set_compare_match_PIN05(CompareMatch compare_match) {
        set_compare_match_Ch_B(compare_match);
    }

    void set_OCR0B(uint8_t new_value) {
        OCR0B = new_value;
    }

    uint8_t get_OCR0B() {
        return OCR0B;
    }

    void set_duty_cycle_Ch_B(uint8_t duty) {
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

    void set_duty_cycle_PD5(uint8_t duty) {
        set_duty_cycle_Ch_B(duty);
    }

    void set_duty_cycle_PIN05(uint8_t duty) {
        set_duty_cycle_Ch_B(duty);
    }

    uint8_t get_duty_cycle_Ch_B() {
        return get_OCR0B();
    }

    uint8_t get_duty_cycle_PD5() {
        return get_OCR0B();
    }

    uint8_t get_duty_cycle_PIN05() {
        return get_OCR0B();
    }
}

namespace Timer1 {

    // Cache the state of the Timer1 module
    static Mode currentMode_;
    static Prescale currentPrescale_;

    void set_mode(Mode mode) {
        switch(mode) {
            case Mode::Normal:
                CLEAR_BIT(TCCR1A, WGM10);
                CLEAR_BIT(TCCR1A, WGM11);
                CLEAR_BIT(TCCR1B, WGM12);
                CLEAR_BIT(TCCR1B, WGM13);
                break;
            case Mode::PhaseCorrectPWM08:
                SET_BIT(TCCR1A, WGM10);
                CLEAR_BIT(TCCR1A, WGM11);
                CLEAR_BIT(TCCR1B, WGM12);
                CLEAR_BIT(TCCR1B, WGM13);
                break;
            case Mode::PhaseCorrectPWM09:
                CLEAR_BIT(TCCR1A, WGM10);
                SET_BIT(TCCR1A, WGM11);
                CLEAR_BIT(TCCR1B, WGM12);
                CLEAR_BIT(TCCR1B, WGM13);
                break;
            case Mode::PhaseCorrectPWM10:
                SET_BIT(TCCR1A, WGM10);
                SET_BIT(TCCR1A, WGM11);
                CLEAR_BIT(TCCR1B, WGM12);
                CLEAR_BIT(TCCR1B, WGM13);
                break;
            case Mode::CTC:
                CLEAR_BIT(TCCR1A, WGM10);
                CLEAR_BIT(TCCR1A, WGM11);
                SET_BIT(TCCR1B, WGM12);
                CLEAR_BIT(TCCR1B, WGM13);
                break;
            case Mode::FastPWM08:
                SET_BIT(TCCR1A, WGM10);
                CLEAR_BIT(TCCR1A, WGM11);
                SET_BIT(TCCR1B, WGM12);
                CLEAR_BIT(TCCR1B, WGM13);
                break;
            case Mode::FastPWM09:
                CLEAR_BIT(TCCR1A, WGM10);
                SET_BIT(TCCR1A, WGM11);
                SET_BIT(TCCR1B, WGM12);
                CLEAR_BIT(TCCR1B, WGM13);
                break;
            case Mode::FastPWM10:
                SET_BIT(TCCR1A, WGM10);
                SET_BIT(TCCR1A, WGM11);
                SET_BIT(TCCR1B, WGM12);
                CLEAR_BIT(TCCR1B, WGM13);
                break;
            case Mode::PhaseFreqCorrect_InputTop:
                CLEAR_BIT(TCCR1A, WGM10);
                CLEAR_BIT(TCCR1A, WGM11);
                CLEAR_BIT(TCCR1B, WGM12);
                SET_BIT(TCCR1B, WGM13);
                break;
            case Mode::PhaseFreqCorrect_OutputTop:
                SET_BIT(TCCR1A, WGM10);
                CLEAR_BIT(TCCR1A, WGM11);
                CLEAR_BIT(TCCR1B, WGM12);
                SET_BIT(TCCR1B, WGM13);
                break;
            case Mode::PhaseCorrect_InputTop:
                CLEAR_BIT(TCCR1A, WGM10);
                SET_BIT(TCCR1A, WGM11);
                CLEAR_BIT(TCCR1B, WGM12);
                SET_BIT(TCCR1B, WGM13);
                break;
            case Mode::PhaseCorrect_OutputTop:
                SET_BIT(TCCR1A, WGM10);
                SET_BIT(TCCR1A, WGM11);
                CLEAR_BIT(TCCR1B, WGM12);
                SET_BIT(TCCR1B, WGM13);
                break;
            case Mode::CTC_InputTop:
                CLEAR_BIT(TCCR1A, WGM10);
                CLEAR_BIT(TCCR1A, WGM11);
                SET_BIT(TCCR1B, WGM12);
                SET_BIT(TCCR1B, WGM13);
                break;
            case Mode::FastPWM_InputTop:
                CLEAR_BIT(TCCR1A, WGM10);
                SET_BIT(TCCR1A, WGM11);
                SET_BIT(TCCR1B, WGM12);
                SET_BIT(TCCR1B, WGM13);
                break;
            case Mode::FastPWM_OutputTop:
                SET_BIT(TCCR1A, WGM10);
                SET_BIT(TCCR1A, WGM11);
                SET_BIT(TCCR1B, WGM12);
                SET_BIT(TCCR1B, WGM13);
                break;
        }

        currentMode_ = mode;
    }

    void set_prescaler(Prescale newPrescale) {
        switch(newPrescale) {
            case Prescale::None:
                SET_BIT(TCCR1B, CS10);
                CLEAR_BIT(TCCR1B, CS11);
                CLEAR_BIT(TCCR1B, CS12);
                break;
            case Prescale::P8:
                CLEAR_BIT(TCCR1B, CS10);
                SET_BIT(TCCR1B, CS11);
                CLEAR_BIT(TCCR1B, CS12);
                break;
            case Prescale::P64:
                SET_BIT(TCCR1B, CS10);
                SET_BIT(TCCR1B, CS11);
                CLEAR_BIT(TCCR1B, CS12);
                break;
            case Prescale::P256:
                CLEAR_BIT(TCCR1B, CS10);
                CLEAR_BIT(TCCR1B, CS11);
                SET_BIT(TCCR1B, CS12);
                break;
            case Prescale::P1024:
                SET_BIT(TCCR1B, CS10);
                CLEAR_BIT(TCCR1B, CS11);
                SET_BIT(TCCR1B, CS12);
                break;
        }
        currentPrescale_ = newPrescale;
    }

    uint8_t get_prescale(){
        return static_cast<uint8_t>(currentPrescale_);
    }

    uint16_t get_max() {
        switch(currentMode_) {
            case Mode::Normal:
                return 0xFFFF;
            case Mode::PhaseCorrectPWM08:
            case Mode::FastPWM08:
                return 0x00FF;
            case Mode::PhaseCorrectPWM09:
            case Mode::FastPWM09:
                return 0x01FF;
            case Mode::PhaseCorrectPWM10:
            case Mode::FastPWM10:
                return 0x03FF;
            case Mode::CTC:
            case Mode::PhaseFreqCorrect_OutputTop:
            case Mode::PhaseCorrect_OutputTop:
            case Mode::FastPWM_OutputTop:
            case Mode::PhaseFreqCorrect_InputTop:
            case Mode::PhaseCorrect_InputTop:
            case Mode::CTC_InputTop:
            case Mode::FastPWM_InputTop:
                return 0xFFFF;
        }
    }

    uint16_t get_top() {
        switch(currentMode_) {
            case Mode::Normal:
                return 0xFFFF;
            case Mode::PhaseCorrectPWM08:
            case Mode::FastPWM08:
                return 0x00FF;
            case Mode::PhaseCorrectPWM09:
            case Mode::FastPWM09:
                return 0x01FF;
            case Mode::PhaseCorrectPWM10:
            case Mode::FastPWM10:
                return 0x03FF;
            case Mode::CTC:
            case Mode::PhaseFreqCorrect_OutputTop:
            case Mode::PhaseCorrect_OutputTop:
            case Mode::FastPWM_OutputTop:
                {
                    uint16_t value;
                    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                        value = OCR1A;
                    }
                    return value;
                }
            case Mode::PhaseFreqCorrect_InputTop:
            case Mode::PhaseCorrect_InputTop:
            case Mode::CTC_InputTop:
            case Mode::FastPWM_InputTop:
                {
                    uint16_t value;
                    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                        value = ICR1;
                    }
                    return value;
                }
        }
    }

    void set_top(uint16_t newTop) {
        switch(currentMode_) {
            //
            // Ignore this method in cases where you cannot set top due to the mode!
            //
            case Mode::Normal:
            case Mode::PhaseCorrectPWM08:
            case Mode::FastPWM08:
            case Mode::PhaseCorrectPWM09:
            case Mode::FastPWM09:
            case Mode::PhaseCorrectPWM10:
            case Mode::FastPWM10:
                break;
            case Mode::CTC:
            case Mode::PhaseFreqCorrect_OutputTop:
            case Mode::PhaseCorrect_OutputTop:
            case Mode::FastPWM_OutputTop:
                {
                    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                        OCR1A = newTop;
                    }
                }
                break;
            case Mode::PhaseFreqCorrect_InputTop:
            case Mode::PhaseCorrect_InputTop:
            case Mode::CTC_InputTop:
            case Mode::FastPWM_InputTop:
                {
                    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                        ICR1 = newTop;
                    }
                }
        }
    }

    void set_frequency(uint16_t hertz) {
        //
        // This function assumes you are in a mode where you can set TOP
        //

        // Get values as floats for computation
        const uint32_t f_cpu = static_cast<float>(F_CPU);
        const float hz = static_cast<float>(hertz);
        const float mx = static_cast<float>(get_max()) + 1.0;

        // Detect if frequency must be scaled by 1.0 for fast PWM
        float fast_or_phase_factor = 2.0; // not fast PWM
        if(currentMode_ == Mode::FastPWM_InputTop || currentMode_ == Mode::FastPWM_OutputTop)
            fast_or_phase_factor = 1.0;

        // Calculate the minimum integer prescale value, then map it to allowed values
        uint32_t prescale = static_cast<uint32_t>(f_cpu / mx / hz / fast_or_phase_factor);
        
        if(prescale < static_cast<uint32_t>(Prescale::None))      set_prescaler(Prescale::None );
        else if(prescale < static_cast<uint32_t>(Prescale::P8))   set_prescaler(Prescale::P8   );
        else if(prescale < static_cast<uint32_t>(Prescale::P64))  set_prescaler(Prescale::P64  );
        else if(prescale < static_cast<uint32_t>(Prescale::P256)) set_prescaler(Prescale::P256 );
        // Maybe not good enough, but try your best
        else                                                      set_prescaler(Prescale::P1024);

        // Calculate Top
        uint16_t top = F_CPU / static_cast<uint16_t>(currentPrescale_) / fast_or_phase_factor / hertz;
        if((currentMode_ == Mode::FastPWM_InputTop || currentMode_ == Mode::FastPWM_OutputTop) && top > 0)
            top -= 1;

        set_top(top);
    }

    void set_OCR1A(uint16_t newValue) {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            OCR1A = newValue;
        }
    }

    uint16_t get_OCR1A() {
        uint16_t value;
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            value = OCR1A;
        }
        return value;
    }

    void set_duty_cycle_Ch_A(uint16_t newDuty) { 
        // We have to special case this for the case of 0 duty, see last  2 paragraphs of section
        // 16.9.3 on the data sheet.
        static uint16_t oldDuty = 0;

        // Turn it off for special case of 0
        if( newDuty == 0) CLEAR_BIT(DDRB, PB1);

        // If it was 0, turn it back on
        else if( newDuty != 0 && oldDuty == 0) SET_BIT(DDRB, PB1);
        
        // Remember old value
        oldDuty = get_OCR1A();

        // Set the duty
        set_OCR1A(newDuty);
    }

    void set_duty_cycle_PB1(uint16_t newDuty) { 
        set_duty_cycle_Ch_A(newDuty);
    }

    void set_duty_cycle_PIN09(uint16_t newDuty) { 
        set_duty_cycle_Ch_A(newDuty);
    }

    uint16_t get_duty_cycle_Ch_A() { 
        return get_OCR1A();
    }

    uint16_t get_duty_cycle_PB1() { 
        return get_OCR1A();
    }

    uint16_t get_duty_cycle_PIN09() { 
        return get_OCR1A();
    }

    void set_compare_match_Ch_A(CompareMatch compareMatch) {
        switch(compareMatch) {
            case CompareMatch::Clear:
            case CompareMatch::NonInverting:
            case CompareMatch::ClearUp:
                CLEAR_BIT(TCCR1A, COM1A0);
                SET_BIT(TCCR1A, COM1A1);           
                break;
            case CompareMatch::Set:
            case CompareMatch::Inverting:
            case CompareMatch::ClearDown:
                SET_BIT(TCCR1A, COM1A0);
                SET_BIT(TCCR1A, COM1A1);  
                break;
        }
    }

    void set_compare_match_PB1(CompareMatch compareMatch) {
        set_compare_match_Ch_A(compareMatch);
    }

    void set_compare_match_PIN09(CompareMatch compareMatch) {
        set_compare_match_Ch_A(compareMatch);
    }

    void set_OCR1B(uint16_t newValue) {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            OCR1B = newValue;
        }
    }

    uint16_t get_OCR1B() {
        uint16_t value;
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            value = OCR1B;
        }
        return value;
    }

    void set_duty_cycle_Ch_B(uint16_t newDuty) { 
        // We have to special case this for the case of 0 duty, see last  2 paragraphs of section
        // 16.9.3 on the data sheet.
        static uint16_t oldDuty = 0;

        // Turn it off for special case of 0
        if( newDuty == 0) CLEAR_BIT(DDRB, PB2);

        // If it was 0, turn it back on
        else if( newDuty != 0 && oldDuty == 0) SET_BIT(DDRB, PB2);
        
        // Remember old value
        oldDuty = get_OCR1B();

        // Set the duty
        set_OCR1B(newDuty);
    }

    void set_duty_cycle_PB2(uint16_t newDuty) { 
        set_duty_cycle_Ch_B(newDuty);
    }

    void set_duty_cycle_PIN10(uint16_t newDuty) { 
        set_duty_cycle_Ch_B(newDuty);
    }

    uint16_t get_duty_cycle_Ch_B() { 
        return get_OCR1B();
    }

    uint16_t get_duty_cycle_PB2() { 
        return get_OCR1B();
    }

    uint16_t get_duty_cycle_PIN10() { 
        return get_OCR1B();
    }
}

namespace Timer2 {

    // Timer specific (applies to both channels A and B)
    void set_mode(Mode mode) {
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
    }

    void set_prescale(Prescale prescale) {
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

    // Channel A
    void set_compare_match_Ch_A(CompareMatch compare_match) {
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

    void set_compare_match_PB3(CompareMatch compare_match) {
        set_compare_match_Ch_A(compare_match);
    }

    void set_compare_match_PIN11(CompareMatch compare_match) {
        set_compare_match_Ch_A(compare_match);
    }

    void set_OCR2A(uint8_t new_value) {
        OCR2A = new_value;
    }

    uint8_t get_OCR2A() {
        return OCR2A;
    }

    void set_duty_cycle_Ch_A(uint8_t duty) {
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

    void set_duty_cycle_PB3(uint8_t duty) {
        set_duty_cycle_Ch_A(duty);
    }

    void set_duty_cycle_PIN11(uint8_t duty) {
        set_duty_cycle_Ch_A(duty);
    }

    uint8_t get_duty_cycle_Ch_A() {
        return get_OCR2A();
    }

    uint8_t get_duty_cycle_PB3() {
        return get_OCR2A();
    }
    
    uint8_t get_duty_cycle_PIN11() {
        return get_OCR2A();
    }
    

    // Channel B
    void set_compare_match_Ch_B(CompareMatch compare_match) {
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

    void set_compare_match_PD3(CompareMatch compare_match) {
        set_compare_match_Ch_B(compare_match);
    }

    void set_compare_match_PIN03(CompareMatch compare_match) {
        set_compare_match_Ch_B(compare_match);
    }

    void set_OCR2B(uint8_t new_value) {
        OCR2B = new_value;
    }

    uint8_t get_OCR2B() {
        return OCR2B;
    }

    void set_duty_cycle_Ch_B(uint8_t duty) {
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

    void set_duty_cycle_PD3(uint8_t duty) {
        set_duty_cycle_Ch_B(duty);
    }

    void set_duty_cycle_PIN03(uint8_t duty){
        set_duty_cycle_Ch_B(duty);
    }

    uint8_t get_duty_cycle_Ch_B() {
        return get_OCR2B();
    }

    uint8_t get_duty_cycle_PD3() {
        return get_OCR2B();
    }

    uint8_t get_duty_cycle_PIN03()
    {
        return get_OCR2B();
    }
}