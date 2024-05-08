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
	uint8_t Mode_OCnx;
}PWM;

#define TOGGLE_OCx		1
#define CLEAR_OCx		2
#define SET_OCx			3

void PWM_Init(PWM *pwm);




#endif /* PWM_H_ */