#include "Timer.h"

void Timer_init(TIMER *timer)
{
	if(timer->Timerx == TIMER0)
	{
		CLEAR_BIT(TCCR0A, 0xFF);
		CLEAR_BIT(TCCR0B, 0xFF);
		CLEAR_BIT(TIMSK0, 0xFF);
		TCNT0 = 0;
		SET_BIT(TCCR0B, (timer->Prescaler) << CS00);

		if(timer->Mode == NORMAL_MODE)
		{
			TCNT0 = (uint8_t)timer->TCNT_value;
			TIMSK0 |= (1 << TOIE0);
		}
		else if(timer->Mode == CTC_MODE)
		{
			SET_BIT(TCCR0A, (2 << WGM00));
			TCNT0 = (uint8_t)timer->TCNT_value;
			OCR0A = (uint8_t)timer->OCRA_value-1;
			TIMSK0 |= (1 << OCIE0A);
		}
	}
	else if(timer->Timerx == TIMER1)
	{
		CLEAR_BIT(TCCR1A, 0xFF);
		CLEAR_BIT(TCCR1B, 0xFF);
		CLEAR_BIT(TIMSK1, 0xFF);

		TCCR1B |= (timer->Prescaler << CS00);
		if(timer->Mode == NORMAL_MODE)
		{
			TCNT1   = timer->TCNT_value;
			TIMSK1 |= (1 << TOIE1);
		}
		else if(timer->Mode == CTC_MODE)
		{
			SET_BIT(TCCR1B, (1 << WGM12));
			TCNT1 = 0;
			OCR1AH = (timer->OCRA_value >> 8) & 0xFF;
			OCR1AL = timer->OCRA_value & 0xFF;
			OCR1A  = (OCR1AH << 8) | OCR1AL;
			TIMSK1 |= (1 << OCIE1A);
		}
	}
	sei();
}

void Clear_Interrupt_Flag(TIMER *timer)
{
	if(timer->Timerx == TIMER0)
	{
		if(timer->Mode == NORMAL_MODE)
		{
			while(!(TIFR0 & (1 << TOV0)));
			TIFR0 |= (1 << TOV0);
		}
		else if(timer->Mode == CTC_MODE)
		{
			while(!(TIFR0 & (1 << OCF0A)) || !(TIFR0 & (1 << OCF0B)));
			TIFR0 |= (1 << OCF0A) | (1 << OCF0B);
		}
	}
	else if(timer->Timerx == TIMER1)
	{
		if(timer->Mode == NORMAL_MODE)
		{
			while(!(TIFR1 & (1 << TOV1)));
			TIFR1 |= (1 << TOV1);
		}
		else if(timer->Mode == CTC_MODE)
		{
			while(!(TIFR1 & (1 << OCF1A)) || !(TIFR1 & (1 << OCF1B)));
			TIFR1 |= (1 << OCF1A) | (1 << OCF1B);
		}
	}
}
void Reload_TCNT_value(TIMER *timer)
{
	if(timer->Timerx == TIMER0)
	{
		TCNT0 = timer->TCNT_value;
	}
	else if(timer->Timerx == TIMER1)
	{
		TCNT1 = timer->TCNT_value;
	}
}

void Reload_OCR_value(TIMER *timer)
{
	if(timer->Timerx == TIMER0)
	{
		OCR0A = (uint8_t)timer->OCRA_value;
		OCR0B = (uint8_t)timer->OCRB_value;
	}

	else if(timer->Timerx == TIMER1)
	{
		OCR1A = timer->OCRA_value;
		OCR1B = timer->OCRB_value;
	}
}
