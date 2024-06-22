#include "delay.h"

void delay_us(u32 time)
{
	while(time--)
	{
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
	}
}

void delay_ms(u32 time)
{
	while(time--)
	{
		delay_us(1000);
	}
}