/*
 * button_debounce.c
 *
 * Created: 3/25/24 06:07:11 PM
 * Author : TuTran
 */ 

#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#define LED1 PE4
#define BUTTON PE5

typedef struct
{
	uint8_t acc;
} button_t;

inline void button_update(button_t *button, uint8_t pin_value)
{
	button->acc = pin_value;
}

volatile uint8_t tick = 0;

int main(void)
{
	button_t button = {0};

	// setting port direction and pull up resistors
	DDRE |= (1<<LED1);
	PORTE |= (1<<BUTTON);
	while (1)
	{
		
		button_update(&button, (PINE >> BUTTON) & 0x01);
		switch (button.acc)
		{
			case 0x00:
			PORTE ^= (1 << LED1);
			break;
			break;
			default:
			break;
		}
	}
}

