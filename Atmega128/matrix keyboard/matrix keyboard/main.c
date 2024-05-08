/*
 * matrix keyboard.c
 *
 * Created: 3/18/24 09:28:37 PM
 * Author : TuTran
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
	uint8_t row[4] = {0x70, 0x68, 0x58, 0x38};
	uint8_t col[3] = {0x76, 0x75, 0x73};
	uint8_t olvas = 0;
	int sor = 0x08;
	uint8_t shift = 3;
    DDRC = 0x78;
	DDRB = 0xFF;

	while(1)
	{
		for(uint8_t i = 0; i < 4; i++)
		{
			PORTC = row[i];
			_delay_ms(30);
			for(uint8_t j = 0; j < 3; j++)
			{
				if((PINC&0x7F) == col[j])
				{
					return j;
				}
				else
				{
					PORTB &= ~(1<<PB0);
				}	
			}
			
		}

	}

	
	return 0;
	 
}

