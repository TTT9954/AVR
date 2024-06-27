#ifndef TIMER_H
#define TIMER_H

#include "std_type.h"

typedef struct Timer
{
   uint8_t Timerx; // Timer0, Timer1, ...
   uint8_t Mode; // Normal mode, CTC mode, ...
   uint8_t Prescaler; // Pres8, pres64, ...
   uint16_t TCNT_value;
   uint16_t OCRA_value;
   uint16_t OCRB_value;
}TIMER;



/* Timerx */	
#define TIMER0  0
#define TIMER1  1
#define TIMER2  2
#define TIMER3  3
#define TIMER4  4
#define TIMER5  5

/* Mode Timer */	
#ifdef TIMER0
#define NORMAL_MODE					0
#define PHASE_CORRECT_TOP_0xFF		1 // TOP = 0xFF
#define CTC_MODE					2
#define FAST_PWM_MODE_TOP_0xFF		3 // TOP = 0xFF
#define PHASE_CORRECT_TOP_OCRA		5
#define FAST_PWM_MODE_TOP_OCRA		7 // TOP = 0xFF
#endif

#if defined (TIMER1)  || defined (TIMER3) || defined (TIMER4) || defined (TIMER5) 
#define NORMAL_MODE					0
#define PHASE_CORRECT_TOP_8BIT		1 // TOP = 0x00FF
#define PHASE_CORRECT_TOP_9BIT		2 // TOP = 0x01FF
#define PHASE_CORRECT_TOP_10BIT		3 // TOP = 0x03FF
#define CTC_MODE_OCRnA				4 // TOP = OCRnA
#define FAST_PWM_8BIT				5 // TOP = 0x00FF
#define FAST_PWM_9BIT				6 // TOP = 0x01FF
#define FAST_PWM_10BIT				7 // TOP = 0x03FF
#define PHASE_FREQ_CORRECT_ICRn		8 // TOP = ICRn
#define PHASE_FREQ_CORRECT_OCRnA	9 // TOP = OCRnA	
#define PHASE_CORRECT_ICR			10 // TOP = ICRn
#define PHASE_CORRECT_OCRnA			11 // TOP = OCRnA
#define CTC_MODE_ICRn				12 // TOP = ICRn
#define FAST_PWM_ICRn				14 // TOP = ICRn
#define FAST_PWM_OCRnA				15 // TOP = OCRnA
#endif


/* Prescaler Timer */	
#define PRES_1						1
#define PRES_8						2
#define PRES_64						3
#define PRES_256					4
#define PRES_1024					5

void Timer_init(TIMER *timer);
void Reload_TCNT_value(TIMER *timer);
void Reload_OCR_value(TIMER *timer);
void Clear_Interrupt_Flag(TIMER *timer);
#endif 