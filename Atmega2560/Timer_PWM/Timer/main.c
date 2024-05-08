#include "Timer.h"
#include "PWM.h"

#define BUTTON_PIN    PD3
#define LED_PIN_1     PD2
#define LED_PIN_2     PB7


uint8_t read = 0;
uint8_t state = 0;

TIMER timer0 = {TIMER0, NORMAL_MODE, PRES_64, 131, 0};
TIMER timer1 = {TIMER1, CTC_MODE, PRES_64, 0, 12500};

void PWM_configure(uint8_t Mode_PWM, uint8_t Mode_OCnx)
{
	PWM pwm_fastmode;
	
	pwm_fastmode.timerx.Timerx = TIMER1;
	pwm_fastmode.Mode_PWM = Mode_PWM;
	pwm_fastmode.Mode_OCnx = Mode_OCnx;

	PWM_Init(&pwm_fastmode);
}
int main(void)
{
	//debug_init();
	CLKPR |= (1 << CLKPS0);
	DDRD  &= ~(1 << BUTTON_PIN);
	DDRD  |= (1 << LED_PIN_1);
	DDRB  |= 0xFF;
	PORTD = PORTB = 0;

	Timer_init(&timer0);
	//Timer_init(&timer1);
	PWM_configure(FAST_PWM_MODE_TOP_0xFF, TOGGLE_OCx);

	sei();
	while(1)
	{	

	}

}


ISR(TIMER1_COMPA_vect)
{
	static volatile uint16_t count = 0;

	Reload_OCR_value(&timer1);
	count++;
	if(count == 1)
	{
		PORTB ^= (1 << LED_PIN_2);
		count = 0;
	}
}

ISR(TIMER0_OVF_vect)
{
	static volatile uint16_t count = 0;

	Reload_TCNT_value(&timer0);
	count++;
	if(count == 100)
	{
		PORTD ^= (1 << LED_PIN_1);
		count = 0;
	}
}



