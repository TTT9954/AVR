#include "PWM.h"

void PWM_Init(PWM *pwm)
{ 
	pwm->timerx.Mode = pwm->Mode_PWM;
	if(pwm->timerx.Timerx == TIMER0)
	{
		CLEAR_BIT(TCCR0A, 0xFF);
		CLEAR_BIT(TCCR0B, 0xFF);
		CLEAR_BIT(TIMSK0, 0xFF);
		TCNT0 = 0;
		SET_BIT(TCCR0B, (pwm->timerx.Prescaler) << CS00);
		
		switch(pwm->Mode_PWM)
		{
			case FAST_PWM_MODE_TOP_0xFF:
			{
				SET_BIT(TCCR0A, (3 << WGM00));
				if(pwm->Channelx == CHANNEL_A)
				{
					DDRB |= (1 << OC0A);
					SET_BIT(TCCR0A, (pwm->Mode_OCnx << COM0A0));
				}
				else if(pwm->Channelx == CHANNEL_B)
				{
					DDRG |= (1 << OC0B);
					SET_BIT(TCCR0A, (pwm->Mode_OCnx << COM0B0));
				}				
				break;
			}
			case FAST_PWM_MODE_TOP_OCRA:
			{
				if(pwm->Mode_OCnx == TOGGLE_OCx)
				{
					SET_BIT(TCCR0A, (TOGGLE_OCx << COM0B0));
				}
				else if(pwm->Mode_OCnx ==  CLEAR_OCx)
				{
					SET_BIT(TCCR0A, (CLEAR_OCx << COM0B0));
				}
				else if(pwm->Mode_OCnx ==  SET_OCx)
				{
					SET_BIT(TCCR0A, (SET_OCx << COM0B0));
				}
				break;
			}
			default: 
				break;		
		}
		
	}
	else if(pwm->timerx.Timerx == TIMER1)
	{
		CLEAR_BIT(TCCR1A, 0xFF);
		CLEAR_BIT(TCCR1B, 0xFF);
		CLEAR_BIT(TIMSK1, 0xFF);
		TCNT1 = 0;
		SET_BIT(TCCR1B, (pwm->timerx.Prescaler) << CS00);
		
		switch(pwm->Mode_PWM)
		{
			case FAST_PWM_8BIT:
			{
				SET_BIT(TCCR1A, (1 << WGM10));
				SET_BIT(TCCR1B, (1 << WGM12));
				if(pwm->Channelx == CHANNEL_A)
				{
					DDRB |= (1 << OC1A);
					SET_BIT(TCCR1A, (pwm->Mode_OCnx << COM1A0));
				}
				else if(pwm->Channelx == CHANNEL_B)
				{
					DDRB |= (1 << OC1B);
					SET_BIT(TCCR1A, (pwm->Mode_OCnx << COM1B0));
				}
				else if(pwm->Channelx == CHANNEL_C)
				{
					DDRC |= (1 << OC1C);
					SET_BIT(TCCR1A, (pwm->Mode_OCnx << COM1C0));
				}
				break;
			}
			case FAST_PWM_ICRn:
			{
				SET_BIT(TCCR1A, (1 << WGM11));
				SET_BIT(TCCR1B, (1 << WGM13)|(1 << WGM12));
				break;
			}
			default: break;
		}
	}	
}
