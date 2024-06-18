#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
//#include "app_api.h"

#include "Timer.h"

#define BUTTON_PIN    PD3
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

volatile uint16_t count = 0;
volatile uint8_t count1 = 0;

uint8_t brightness = 0;
const uint8_t brightnessLevel[16] = {0, 1, 2, 3, 5, 7, 10, 15, 26, 32, 39, 46, 57, 67, 80, 100};

uint8_t LedNum[8];

void pattern1();
void pattern2();

int main(void)
{
	uint8_t a = 0x08;
	uint8_t b = 0x10;
	uint8_t flag = 0;
	
	DDRx(0xFF, DDRF, OUTPUT);

	PORTx(0xFF, PORTF, LOW);
	
	while(1)
	{

	}
}

ISR(TIMER1_OVF_vect)
{
	TCNT1 = 65535;
	
}

void pattern1()
{
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
}

void pattern2()
{

}



