#include <string.h>
#include <stdint.h>

#include "Timer/Timer.h"
#include "74HC595/74HC595.h"

#define NUMBER_LED     8

typedef union
{
	uint8_t ODR;
	struct
	{
		uint8_t P0: 1;
		uint8_t P1: 1;
		uint8_t P2: 1;
		uint8_t P3: 1;
		uint8_t P4: 1;
		uint8_t P5: 1;
		uint8_t P6: 1;
		uint8_t P7: 1;
	} PIN_t;
	
} HC595_REG_t;


HC595_REG_t REG1;

volatile UL count = 0;
volatile uint32_t count1 = 0;

TIMER timer0 = {TIMER0, CTC_MODE, PRES_1, 0, 255, 0};

TIMER timer1 = {TIMER1, CTC_MODE_OCRnA, PRES_1, 0, 500, 0};

volatile uint8_t duty = 0;
uint8_t idLedCode[NUMBER_LED] = {1, 2, 4, 8, 16, 32, 64, 128};
const uint8_t mode_arr[8] = {0,1,2,3,4,5,6,7};
const uint8_t  dosangtb[16] = {0, 1, 2, 3 , 5, 7, 10, 15, 20, 26, 32, 39, 47, 60, 75, 90};
uint8_t hc595_reg = 0;
uint8_t ShiftCount = 8;
uint8_t save = 0x00;
uint8_t mode = 0;
uint8_t led_tmp = 0x1;
UL time_tmp1 = 0;
UL time_tmp2 = 0;
volatile uint8_t col_keyboard = 0x06;


uint8_t flag = 0;
uint8_t  dosang[NUMBER_LED];

void Led_chaser(uint8_t mode);
void Hieu_ung_sao_bang(uint8_t speed);
void Led_dimmer_pattern();
void Scan_MatrixKeyboard();

int main(void)
{
	DDRx(0xFF, DDRK, OUTPUT);
	
	DDRx(0xFF, DDRL, INPUT);
	
	DDRx(0xFF, DDRJ, OUTPUT);

	HC595Init();
	
	HC595_OE_LOW();
	
	Timer_init(&timer0);
	//Timer_init(&timer1);

	memset(&REG1, 0, sizeof(REG1));
	uint8_t i = 0x06;
	
	PORTJ = 0xFF;
	while(1)
	{			
		if(led_tmp == 0xFF) led_tmp &= 0x00;
		else 
		{
			led_tmp |= 1;	
			_delay_ms(5);
			led_tmp <<= 1;
		}
		if(count - time_tmp1 > 1)
		{
			time_tmp1 = count;
			duty++;
			if(duty > 100) 
			{
				duty = 0;	
				led_tmp &= 0x00;
			}
		}	
	}
}

ISR(TIMER0_COMPA_vect)
{
	static volatile uint16_t dutyOn = 0;
	OCR0A = 255;
	TCNT0 = 0;
	Transmit_HC595(REG1.ODR);
	count++;
	if(dutyOn < duty)
	{
		REG1.ODR = led_tmp;
	}
	else
	{
		REG1.ODR &= ~(led_tmp);
	}
	if(dutyOn++ > 100) 
	{
		dutyOn = 0;
	}
}

void Hieu_ung_sao_bang(uint8_t speed)
{
	dosang[2] =  dosangtb[15];
	dosang[1] =  dosangtb[8];
	dosang[0] =  dosangtb[1];
	
	while(1)
	{
		uint8_t ds  = dosang[7];
		for(uint8_t CountLed = 7; CountLed > 0; CountLed--)
		{
			dosang[CountLed] = dosang[CountLed - 1] ;
		}
		dosang[0] = ds;
		
		_delay_ms(speed);
	}
}

void Led_chaser(uint8_t mode)
{
	static uint8_t i = 0;
	static uint8_t led = 0x01;

	if(mode == 0)
	{
		REG1.ODR = led;
		if(count == 100)
		{
			count = 0;
			if(led == 0x80)
			{
				count = 0;
				mode++;
				led = 0x01;
			}
			else led <<= 1;
		}
		REG1.ODR = led;
	}
	else if(mode == 1)
	{
		if(i < ShiftCount)
		{
			REG1.ODR = led|save;
			if(count == 100)
			{
				count = 0;
				led <<= 1;
				i++;
			}
		}
		else
		{
			i = 0;
			--ShiftCount;
			save = REG1.ODR;
			led = 0x01;
		}
		if(ShiftCount == 0x0)
		{
			count = 0;
			ShiftCount = 8;
			save = 0x00;
			led = 0x00;
			i = 0;
			mode++;
		}
	}
	else if(mode == 2)
	{
		REG1.ODR = led;
		if((count == 100))
		{
			count = 0;
			led = ~led;
			if(i == 10)
			{
				count = 0;
				mode = 0;
				led = 0x01;
				i = 0;
			}
			else i++;
		}
	}
}


void Led_dimmer_pattern()
{
	static uint8_t i = 3;
	if(mode == 0)
	{
		if(count > 200)
		{
			duty+= 2;
			count = 0;
			led_tmp |= i;
			if(duty > 100)
			{
				duty = 0;
				i <<= 1;
				if(led_tmp == 0xC0)
				{
					i = 0;
					REG1.ODR = 0x00;
					led_tmp = 0x01;
					save = 0;
					mode++;
				}
				else led_tmp <<= 2;
			}
		}		
	}
	else if(mode == 1)
	{
		led_tmp |= 1;
		if(count > 200)
		{
			duty+=2;
			count = 0;
			if(duty > 100)
			{
				duty = 0;
				if(led_tmp > 0x80)
				{
					led_tmp = 0x03;
					mode++;
				}
				else led_tmp <<= 1;
			}
		}		
	}
	else if(mode == 1)
	{
		led_tmp |= 1;
		if(count > 200)
		{
			duty+=2;
			count = 0;
			if(duty > 100)
			{
				duty = 0;
				if(led_tmp > 0x80)
				{
					led_tmp = 0x03;
					mode++;
				}
				else led_tmp <<= 1;
			}
		}
	}

}

void Scan_MatrixKeyboard()
{
	PORTJ = col_keyboard;
	if(PORTJ == 0x1B) col_keyboard = 0x06;
	else
	{
		col_keyboard <<= 1;
		col_keyboard = col_keyboard + 1;
	}	
}