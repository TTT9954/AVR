#include "millis.h"

volatile UL_INT count_millis = 0;

static volatile UL_INT count1 = 0;


static TIMER timer0 = {TIMER0, NORMAL_MODE, PRES_64, 6};
	
static TIMER timer1 = {TIMER0, NORMAL_MODE, PRES_1, 240};


void millis_init()
{
	Timer_init(&timer0);
}

void micros_init()
{
	Timer_init(&timer1);
}

UL_INT millis()
{
	UL_INT timer = count_millis;
	
	return timer;
} 

// 
// ISR(TIMER0_OVF_vect)
// {
// 	TCNT0 = 5;
// 	count_millis++;
// }
