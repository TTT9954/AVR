#include "PWM.h"

void PWM_Init(PWM *pwm)
{ 
	if(pwm->timerx.Timerx == TIMER0)
	{
		Timer_init(&pwm->timerx);
		switch(pwm->Mode_PWM)
		{
			case FAST_PWM_MODE_TOP_0xFF:
			{
				SET_BIT(TCCR0A, (3 << WGM00));
				break;
			}
			case FAST_PWM_MODE_TOP_OCRA:
			{
				SET_BIT(TCCR0A, (3 << WGM00));	
				SET_BIT(TCCR0B, (1 << WGM02));
				break;
			}
			default: 
				break;		
		}
		switch(pwm->Mode_OCnx)
		{
			case TOGGLE_OCx:
			{
				SET_BIT(TCCR0A, (TOGGLE_OCx << COM0A0));
				break;
			}
			case CLEAR_OCx:
			{
				SET_BIT(TCCR0A, (CLEAR_OCx << COM0A0));
				break;
			}
			case SET_OCx:
			{
				SET_BIT(TCCR0A, (SET_OCx << COM0A0));
				break;
			}
			default:
			break;
		}		
	}
	else if(pwm->timerx.Timerx == TIMER1)
	{
		Timer_init(&pwm->timerx);
		switch(pwm->Mode_PWM)
		{
			case FAST_PWM_MODE_TOP_0xFF:
			{
				SET_BIT(TCCR1A, (3 << WGM10));
				break;
			}
			case FAST_PWM_MODE_TOP_OCRA:
			{
				SET_BIT(TCCR1A, (3 << WGM10));
				SET_BIT(TCCR1B, (1 << WGM12));
				break;
			}
			default:
			break;
		}
		switch(pwm->Mode_OCnx)
		{
			case TOGGLE_OCx:
			{
				SET_BIT(TCCR1A, (TOGGLE_OCx << COM0A1));
				break;
			}
			case CLEAR_OCx:
			{
				SET_BIT(TCCR1A, (CLEAR_OCx << COM0A1));
				break;
			}
			case SET_OCx:
			{
				SET_BIT(TCCR1A, (SET_OCx << COM0A1));
				break;
			}
			default:
				break;
		}
	}	
}
