/*
 * PWM.h
 *
 * Created: 5/8/24 06:52:05 PM
 *  Author: TuTran
 */ 


#ifndef PWM_H_
#define PWM_H_

#include "Timer.h"

typedef struct PWM
{
	TIMER timerx;
	uint8_t Mode_PWM;
	uint8_t Channelx;
	uint8_t Mode_OCnx;
}PWM;

#define CHANNEL_A		0
#define CHANNEL_B		1
#define CHANNEL_C		2

#define OC0A			PB7
#define OC1A			PB5
#define OC2A			PB4
#define OC3A			PE3
#define OC4A			PH3

#define OC0B			PG5
#define OC1B			PB6
#define OC2B			PH6
#define OC3B			PE4
#define OC4B			PH4

#define OC1C			PB7
#define OC3C			PE5
#define OC4C			PH5

#define TOGGLE_OCx		1
#define CLEAR_OCx		2
#define SET_OCx			3


void PWM_Init(PWM *pwm);




#endif /* PWM_H_ */