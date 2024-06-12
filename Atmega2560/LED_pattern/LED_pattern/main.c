
#define F_CPU	16000000UL

#include <avr/io.h>
#include <util/delay.h>


#include "Timer/Timer.h"

#define LED_PIN_0     (1 << PF0)
#define LED_PIN_1     (1 << PF1)
#define LED_PIN_2     (1 << PF2)
#define LED_PIN_3     (1 << PF3)
#define LED_PIN_4     (1 << PF4)
#define LED_PIN_5     (1 << PF5)
#define LED_PIN_6     (1 << PF6)
#define LED_PIN_7     (1 << PF7)

#define DDRx(pin,port,state)    ((state == 1) ? (port |= pin) : (port &= ~(pin)))
#define PORTx(pin,port,state)   ((state == 1) ? (port |= pin) : (port &= ~(pin)))
#define TOGGLE(pin, port)       (port ^= pin)

#define HIGH		1
#define LOW			0
#define OUTPUT		1
#define INPUT		0
#define MAX_BRIGHTNESS           100

typedef struct LED
{
	uint8_t Led0;
	uint8_t Led1;
	uint8_t Led2;
	uint8_t Led3;
	uint8_t Led4;
	uint8_t Led5;
	uint8_t Led6;
	uint8_t Led7;
} LEDs;

typedef enum
{
	UP,
	DOWN
} DIRECTION;

LEDs  pwm[10] = {
	{1, 0, 1, 0, 1, 0, 1, 0},
	{0, 1, 0, 1, 0, 1, 0, 1},
};

uint8_t read = 0;
uint8_t state = 0;
uint8_t mode = 0;

volatile uint16_t count = 0;
volatile uint8_t count1 = 0;

uint8_t brightness = 0;
const uint8_t brightnessLevel[16] = {0, 1, 2, 3, 5, 7, 10, 15, 26, 32, 39, 46, 57, 67, 80, 100};

TIMER timer0 = {TIMER1, NORMAL_MODE, PRES_64, 65535, 0, 0};

TIMER timer1 = {TIMER1, NORMAL_MODE, PRES_64, 65535, 0, 0};
	
uint8_t LedNum[8];

void pattern1();
void pattern2();
void pattern3();

int main(void)
{
	DDRx(0xFF, DDRF, OUTPUT);

	PORTF = 0x00;
	
	Timer_init(&timer1);
	
	while(1)
	{
		if(count < 1) PORTx(0xFF, PORTF, HIGH);
		else PORTx(0xFF, PORTF, LOW);
		
		pattern1();
		pattern2();
		pattern3();
	}
}

ISR(TIMER1_OVF_vect)
{
	TCNT1 = 65535;
	
	if(++count == 10) count = 0;
	

}

void pattern1()
{
	while(mode == 0)
	{
		PORTF &= 0x00;
		
		for(uint8_t countDS = 0; countDS < 8; countDS++)
		{
			PORTx(1 << countDS, PORTF,  HIGH);
			_delay_ms(50);
		}
		for(uint8_t countDS = 0; countDS < 8; countDS++)
		{
			PORTx(1 << (7-countDS), PORTF,  LOW);
			_delay_ms(50);
		}	
		mode = 1;		
	}

}

void pattern2()
{
	uint8_t a = 0x08;
	uint8_t b = 0x10;
	uint8_t flag = 0;
	PORTF &= 0;
	while(mode == 1)
	{	
		if(flag == 0)
		{
			PORTF |= (a|b);
			_delay_ms(100);
			if(a == 0x01 && b == 0x80)
			{
				flag = 1;
				a = 0x08;
				b = 0x10;
			}
			else
			{
				a = (a >> 1) & 0x0F;
				b = (b << 1) & 0xF0;
			}
		}
		else if(flag == 1)
		{
			PORTF &= ~(a|b);
			_delay_ms(100);
			if(a == 0x01 && b == 0x80)
			{
				flag = 0;
				a = 0x08;
				b = 0x10;
				mode = 3;
			}
			else
			{
				a = (a >> 1) & 0x0F;
				b = (b << 1) & 0xF0;
			}
			
		}	
	}
}

void pattern3()
{
	while(mode == 3)
	{
		uint8_t led = 0xC0;
		uint8_t i = 0;
		while(i < 4)
		{
			PORTF = led;
			_delay_ms(500);
			led >>= 2;
			i++;	
		}
		i = 0;
		led = 0x03;
		while(i < 4)
		{
			PORTF = led;
			_delay_ms(500);
			led <<= 2;
			i++;
		}
		mode = 0;
	}
}



