#include "74HC595.h"

void HC595Init()
{
	//Make the Data(DS), Shift clock (SH_CP), Store Clock (ST_CP) lines output
	HC595_DDR|=((1<<HC595_DATA)|(1<<HC595_CLK)|(1<<HC595_LATCH)|(1<<HC595_OE));
}

void Latch595()
{
	HC595_LATCH_ACTIVE();
	HC595_LATCH_DEACTIVE();
}

void Transmit_HC595(uint8_t data)
{
	for(uint8_t i=0;i<8;i++)
	{
		if(data & 0x80)
		{
			//MSB is 1 so output high
			HC595_DATA_HIGH();
		}
		else
		{
			//MSB is 0 so output low
			HC595_DATA_LOW();
		}
		HC595_CLK_HIGH();
		HC595_CLK_LOW();  //Pulse the Clock line
		data=data<<1;
	}
	Latch595();
	
	
}

void Wait()
{
	for(uint8_t j = 0; j < 10;j++)
	for(uint8_t i=0;i<=200;i++)
	{
		_delay_loop_1(0);
	}
}
