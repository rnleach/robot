#include "timer.h"

template<> volatile TimerValueType<Timers::T0>::ValueType& Registers<Timers::T0>::tcnt = TCNT0;
template<> volatile TimerValueType<Timers::T1>::ValueType& Registers<Timers::T1>::tcnt = TCNT1;
template<> volatile TimerValueType<Timers::T2>::ValueType& Registers<Timers::T2>::tcnt = TCNT2;

template<> volatile TimerValueType<Timers::T0>::ValueType& Registers<Timers::T0>::ocrna = OCR0A;
template<> volatile TimerValueType<Timers::T1>::ValueType& Registers<Timers::T1>::ocrna = OCR1A;
template<> volatile TimerValueType<Timers::T2>::ValueType& Registers<Timers::T2>::ocrna = OCR2A;

template<> volatile TimerValueType<Timers::T0>::ValueType& Registers<Timers::T0>::ocrnb = OCR0B;
template<> volatile TimerValueType<Timers::T1>::ValueType& Registers<Timers::T1>::ocrnb = OCR1B;
template<> volatile TimerValueType<Timers::T2>::ValueType& Registers<Timers::T2>::ocrnb = OCR2B;

template<> volatile uint8_t& Registers<Timers::T0>::tccrna = TCCR0A;
template<> volatile uint8_t& Registers<Timers::T2>::tccrna = TCCR2A;

template<> volatile uint8_t& Registers<Timers::T0>::tccrnb = TCCR0B;
template<> volatile uint8_t& Registers<Timers::T2>::tccrnb = TCCR2B;

template<> 
void Timer<Timers::T0>::set_prescaler(typename PrescalerT<Timers::T0>::PType prescale) {
    switch(prescale) {
        using Prescale = PrescalerT<Timers::T0>::PType;
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

template<> 
void Timer<Timers::T1>::set_prescaler(typename PrescalerT<Timers::T1>::PType prescale) {
    using Prescale = PrescalerT<Timers::T1>::PType;
    switch(prescale) {
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
        currentPrescale_ = prescale;
}

template<> 
void Timer<Timers::T2>::set_prescaler(typename PrescalerT<Timers::T2>::PType prescale) {
    using Prescale = PrescalerT<Timers::T2>::PType;
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
        currentPrescale_ = prescale;
}

template<>
void Timer<Timers::T0>::set_mode(typename ModesT<Timers::T0>::MType mode) {

    using Mode = ModesT<Timers::T0>::MType;

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

    // If not off, ensure we set the prescaler, since it is used to turn the timer on/off
    if(mode != Mode::Off && currentMode_ == Mode::Off) set_prescaler(currentPrescale_);

    currentMode_ = mode;
}

template<>
void Timer<Timers::T1>::set_mode(typename ModesT<Timers::T1>::MType mode) {

    using Mode = ModesT<Timers::T1>::MType;

    // Set the mode
    switch(mode) {
        case Mode::Off:
            CLEAR_BIT(TCCR1B, CS10);
            CLEAR_BIT(TCCR1B, CS11);
            CLEAR_BIT(TCCR1B, CS12);
            // Fall through to normal just to reset all these bits to zero like they would be
            // on a cold start.
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

    // If not off, ensure we set the prescaler, since it is used to turn the timer on/off
    if(mode != Mode::Off && currentMode_ == Mode::Off) set_prescaler(currentPrescale_);

    currentMode_ = mode;
}

template<>
void Timer<Timers::T2>::set_mode(typename ModesT<Timers::T2>::MType mode) {

    using Mode = ModesT<Timers::T2>::MType;

    switch(mode) {
        case Mode::Off:
            CLEAR_BIT(TCCR2B, CS20);
            CLEAR_BIT(TCCR2B, CS21);
            CLEAR_BIT(TCCR2B, CS22);
            // Fall through to normal just to reset all these bits to zero like they would be
            // on a cold start.
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

    // If not off, ensure we set the prescaler, since it is used to turn the timer on/off
    if(mode != Mode::Off && currentMode_ == Mode::Off) set_prescaler(currentPrescale_);

    currentMode_ = mode;
}

template<>
typename TimerValueType<Timers::T1>::ValueType Timer<Timers::T1>::get_max() {
    using Mode = ModesT<Timers::T1>::MType;

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

template<>
typename TimerValueType<Timers::T1>::ValueType Timer<Timers::T1>::get_top() {
    using Mode = typename ModesT<Timers::T1>::MType;
    switch(currentMode_){
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

template<>
void Timer<Timers::T1>::set_top(typename TimerValueType<Timers::T1>::ValueType new_top) {
    using Mode = typename ModesT<Timers::T1>::MType;
    switch(currentMode_){
        // Ignore this method in cases where you cannot set top due to the mode!
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
                    OCR1A = new_top;
                }
            }
            break;
        case Mode::PhaseFreqCorrect_InputTop:
        case Mode::PhaseCorrect_InputTop:
        case Mode::CTC_InputTop:
        case Mode::FastPWM_InputTop:
            {
                ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                    ICR1 = new_top;
                }
            }
    }
}

template<>
void Timer<Timers::T1>::set_frequency(uint16_t hertz){
    //
    // This function assumes you are in a mode where you can set TOP
    //

    using Mode = typename ModesT<Timers::T1>::MType;
    using Prescale = PrescalerT<Timers::T1>::PType;

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

template<>
auto Timer<Timers::T1>::get_count() -> TimerValueType<Timers::T1>::ValueType {

    TimerValueType<Timers::T1>::ValueType value;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        value = Registers<Timers::T1>::tcnt;
    }
    return value;
}

template<> 
void Timer<Timers::T1>::set_count(typename TimerValueType<Timers::T1>::ValueType new_count) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        TCNT1 = new_count;
    }
}

template<>
template<>
void Timer<Timers::T0>::set_ocr<Channels::A>(typename TimerValueType<Timers::T0>::ValueType newValue){
    OCR0A = newValue;
}

template<>
template<>
void Timer<Timers::T1>::set_ocr<Channels::A>(typename TimerValueType<Timers::T1>::ValueType newValue) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        OCR1A = newValue;
    }
}

template<>
template<>
void Timer<Timers::T2>::set_ocr<Channels::A>(typename TimerValueType<Timers::T2>::ValueType newValue){
    OCR2A = newValue;
}

template<>
template<>
auto Timer<Timers::T0>::get_ocr<Channels::A>() -> typename TimerValueType<Timers::T0>::ValueType {
    return Registers<Timers::T0>::ocrna;
}

template<> 
template<>
auto Timer<Timers::T1>::get_ocr<Channels::A>() -> TimerValueType<Timers::T1>::ValueType {
    TimerValueType<Timers::T1>::ValueType value;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        value = Registers<Timers::T1>::ocrna;
    }
    return value;
}

template<>
template<>
auto Timer<Timers::T2>::get_ocr<Channels::A>() -> typename TimerValueType<Timers::T2>::ValueType {
    return Registers<Timers::T2>::ocrna;
}

template<>
template<>
void Timer<Timers::T0>::set_ocr<Channels::B>(typename TimerValueType<Timers::T0>::ValueType newValue){
    Registers<Timers::T0>::ocrnb = newValue;
}

template<>
template<>
void Timer<Timers::T1>::set_ocr<Channels::B>(typename TimerValueType<Timers::T1>::ValueType newValue) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        OCR1B = newValue;
    }
}

template<>
template<>
void Timer<Timers::T2>::set_ocr<Channels::B>(typename TimerValueType<Timers::T2>::ValueType newValue){
    Registers<Timers::T2>::ocrnb = newValue;
}

template<>
template<>
auto Timer<Timers::T0>::get_ocr<Channels::B>() -> typename TimerValueType<Timers::T0>::ValueType {
    return Registers<Timers::T0>::ocrnb;
}

template<> 
template<>
auto Timer<Timers::T1>::get_ocr<Channels::B>() -> TimerValueType<Timers::T1>::ValueType {
    TimerValueType<Timers::T1>::ValueType value;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        value = Registers<Timers::T1>::ocrnb;
    }
    return value;
}

template<>
template<>
auto Timer<Timers::T2>::get_ocr<Channels::B>() -> typename TimerValueType<Timers::T2>::ValueType {
    return Registers<Timers::T2>::ocrnb;
}

template<>
template<> 
void Timer<Timers::T0>::set_compare_match<Channels::A>(typename CompareMatchT<Timers::T0>::CType compareMatch) {
    using CompareMatch = CompareMatchT<Timers::T0>::CType;

    switch(compareMatch) {
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

template<>
template<> 
void Timer<Timers::T0>::set_compare_match<Channels::B>(typename CompareMatchT<Timers::T0>::CType compareMatch) {
    using CompareMatch = CompareMatchT<Timers::T0>::CType;

    switch(compareMatch) {
        case CompareMatch::Clear:
        case CompareMatch::NonInverting:
        case CompareMatch::ClearUp:
            CLEAR_BIT(TCCR0B, COM0B0);
            SET_BIT(TCCR0B, COM0B1);           
            break;
        case CompareMatch::Set:
        case CompareMatch::Inverting:
        case CompareMatch::ClearDown:
            SET_BIT(TCCR0B, COM0B0);
            SET_BIT(TCCR0B, COM0B1);  
            break;
    }
}

template<>
template<> 
void Timer<Timers::T1>::set_compare_match<Channels::A>(typename CompareMatchT<Timers::T1>::CType compareMatch) {
    using CompareMatch = CompareMatchT<Timers::T1>::CType;

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

template<>
template<> 
void Timer<Timers::T1>::set_compare_match<Channels::B>(typename CompareMatchT<Timers::T1>::CType compareMatch) {
    using CompareMatch = CompareMatchT<Timers::T1>::CType;

    switch(compareMatch) {
        case CompareMatch::Clear:
        case CompareMatch::NonInverting:
        case CompareMatch::ClearUp:
            CLEAR_BIT(TCCR1B, COM1B0);
            SET_BIT(TCCR1B, COM1B1);           
            break;
        case CompareMatch::Set:
        case CompareMatch::Inverting:
        case CompareMatch::ClearDown:
            SET_BIT(TCCR1B, COM1B0);
            SET_BIT(TCCR1B, COM1B1);  
            break;
    }
}

template<>
template<> 
void Timer<Timers::T2>::set_compare_match<Channels::A>(typename CompareMatchT<Timers::T2>::CType compareMatch) {
    using CompareMatch = CompareMatchT<Timers::T2>::CType;

    switch(compareMatch) {
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

template<>
template<> 
void Timer<Timers::T2>::set_compare_match<Channels::B>(typename CompareMatchT<Timers::T2>::CType compareMatch) {
    using CompareMatch = CompareMatchT<Timers::T2>::CType;

    switch(compareMatch) {
        case CompareMatch::Clear:
        case CompareMatch::NonInverting:
        case CompareMatch::ClearUp:
            CLEAR_BIT(TCCR2B, COM2B0);
            SET_BIT(TCCR2B, COM2B1);           
            break;
        case CompareMatch::Set:
        case CompareMatch::Inverting:
        case CompareMatch::ClearDown:
            SET_BIT(TCCR2B, COM2B0);
            SET_BIT(TCCR2B, COM2B1);  
            break;
    }
}