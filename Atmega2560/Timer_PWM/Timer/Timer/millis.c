#include "millis.h"

#define TIM0_OVF	TIMER0_OVF_vect

static volatile UUL_INT count = 0;

static volatile UUL_INT count1 = 0;


TIMER timer0 = {TIMER0, NORMAL_MODE, PRES_64, 6};
TIMER timer1 = {TIMER0, NORMAL_MODE, PRES_1, 240};


void millis_init()
{
	Timer_init(&timer0);
}

void micros_init()
{
	Timer_init(&timer1);
}

volatile UUL_INT millis()
{
	volatile UUL_INT timer = count;
	
	return timer;
} 

#ifndef TIMx_OVF
	ISR(TIMER0_OVF_vect)
	{
		Reload_TCNT_value(&timer0);
		count++;
	}
#else 
	ISR(TIM0_OVF)
	{
		static volatile UUL_INT count = 0;
		Reload_TCNT_value(&timer0);
		count++;
	}
#endif