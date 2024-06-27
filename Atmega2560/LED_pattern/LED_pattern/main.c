#include <string.h>
#include <stdint.h>

#include "Timer.h"
#include "Matrix_Keyboard/Matrix_Keyboard.h"
#include "74HC595/74HC595.h"
#include "std_type.h"

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

typedef struct Duty
{
	uint8_t Led_position;
	uint8_t brightnessLevel;
	volatile uint8_t dutyON;
	volatile uint8_t dutyTotal;
} DUTY_t;

typedef struct DurationTimer
{
	uint32_t start;
	uint32_t end;
	UL duration;	
}DURATION_t;

HC595_REG_t REG1;
DUTY_t duty1, duty2, duty3;
DURATION_t time1,time2,time3;
volatile UL count = 0;
volatile uint32_t count1 = 0;

TIMER timer0 = {TIMER0, CTC_MODE, PRES_8, 0, 1, 0};

TIMER timer1 = {TIMER1, CTC_MODE_OCRnA, PRES_1, 0, 500, 0};

uint8_t ShiftCount = 8;
uint8_t save = 0x00;
volatile uint8_t mode = 0;
volatile uint8_t led_tmp = 0x01;
uint8_t brightness = 0;
uint8_t led1 = 0x0F; // led1= 0b00001111
uint8_t led2 = 0x00; // led2= 0b00000000

uint8_t idLedCode[NUMBER_LED] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
const uint8_t mode_arr[8] = {0,1,2,3,4,5,6,7};
const uint8_t  dosangtb[16] = {0, 1, 2, 3 , 5, 7, 10, 15, 20, 26, 32, 39, 47, 60, 75, 90};

uint8_t Led_Patterns[][8] = {
	{0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80},
	{0x18, 0x24, 0x42, 0x81},	
};

uint8_t flag1 = 0;
uint8_t flag2 = 0;
uint8_t  dosang[NUMBER_LED];

void Led_chaser(uint8_t mode);
void Hieu_ung_sao_bang(uint8_t speed);
void Led_dimmer_pattern();
void Scan_MatrixKeyboard();

int main(void)
{
	DDRx(0xFF, DDRK, OUTPUT);

	HC595Init();
	
	HC595_OE_LOW();
	
	Timer_init(&timer0);

	memset(&duty1, 0, sizeof(duty1));
	memset(&duty2, 0, sizeof(duty2));
	memset(&time1, 0, sizeof(time1));
	memset(&time2, 0, sizeof(time2));
	uint8_t i = 0x1;
	uint8_t j = 0;
	duty1.dutyTotal = 0;
	duty2.dutyTotal = 100;
	duty1.brightnessLevel = 2;
	duty2.brightnessLevel = 8;
	duty3.brightnessLevel = 15;
	while(1)
	{
		duty1.Led_position = i;
		if(time1.start - time1.end > 5000)
		{
			time1.start = 0;		
			if(duty1.Led_position == (0x80 >> j)) 
			{
				duty2.Led_position |= duty1.Led_position;
				REG1.ODR = duty2.Led_position;
				i = 0x01;
				j++;
				if(j > 8) 
				{
					j = 0;
					i = 0x01;
					duty2.Led_position = 0x00;
					REG1.ODR &= 0x00;
				}
			}
			else i <<= 1;
		}
		if(time2.start - time2.end > 1000)
		{
			time2.start = 0;
			duty2.dutyTotal = dosangtb[duty2.brightnessLevel];
			duty2.brightnessLevel++;
			if(duty2.brightnessLevel == 15)
			{
				duty2.brightnessLevel = 0;
				flag2 = 0;
			}
		}
// 		if(time1.start - time1.end > 1000)
// 		{
// 			time1.start = 0;		
// 			if(flag1 == 0)
// 			{
// 				duty1.brightnessLevel++;
// 				if(duty1.brightnessLevel > 15 && flag1 == 0)
// 				{
// 					duty1.brightnessLevel = 15;
// 					flag1 = 1;
// 				}
// 			}
// 			else
// 			{
// 				duty1.brightnessLevel--;
// 				if(duty1.brightnessLevel == 0) 
// 				{
// 					duty1.brightnessLevel = 0;
// 					flag1 = 0;
// 				}
// 			}
// 		}
// 		if(time2.start - time2.end > 1000)
// 		{
// 			time2.start = 0;				
// 			if(flag2 == 0)
// 			{
// 				duty2.brightnessLevel--;
// 				if(duty2.brightnessLevel == 0 && flag2 == 0)
// 				{
// 					duty2.brightnessLevel = 0;
// 					flag2 = 1;
// 				}
// 			}
// 			else
// 			{
// 				duty2.brightnessLevel++;
// 				if(duty2.brightnessLevel == 15)
// 				{
// 					duty2.brightnessLevel = 15;
// 					flag2 = 0;
// 				}
// 			}
// 		}

	}

}

ISR(TIMER0_COMPA_vect)
{
	static volatile uint8_t i = 0x0;
	OCR0A = 10;
	TCNT0 = 0;
	++time1.start;
	++time2.start;
	Transmit_HC595(REG1.ODR);
	
	REG1.ODR = duty1.Led_position;
	if(duty2.dutyON < duty2.dutyTotal)
	{
		REG1.ODR |= duty2.Led_position;
	}
	else
	{
		REG1.ODR &= ~duty2.Led_position;
	}
	if(++duty2.dutyON == 100)
	{
		duty2.dutyON = 0;
	}
}

void Hieu_ung_sao_bang(uint8_t speed)
{
	uint8_t i = 0;
	dosang[2] =  dosangtb[15];
	dosang[1] =  dosangtb[10];
	dosang[0] =  dosangtb[3];
	while(i < 5) 
	{
		uint8_t ds1 = dosang[7];
		for(uint8_t CountLed = 7; CountLed > 0; CountLed--)
		{
			dosang[CountLed] = dosang[CountLed - 1];
		}
		dosang[0] = ds1;
		_delay_ms(5);
		i++;		
	}
	i = 0;	
	dosang[7] =  dosangtb[3];
	dosang[6] =  dosangtb[10];
	dosang[5] =  dosangtb[15];
	while(i < 5)
	{
		uint8_t ds2 = dosang[0];
		for(uint8_t CountLed = 0; CountLed < 8; CountLed++)
		{
			dosang[CountLed] = dosang[CountLed + 1];
		}
		dosang[7] = ds2;
		_delay_ms(5);
		i++;
	}
	i = 0;
}

void Led_chaser(uint8_t mode)
{
	static uint8_t i = 0;
	static uint8_t led = 0x01;

	if(mode == 0)
	{
		duty2.Led_position = led;
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
		duty2.Led_position = led;
	}
	else if(mode == 1)
	{
		if(i < ShiftCount)
		{
			duty2.Led_position = led|save;
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
			save = duty2.Led_position;
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
		duty2.Led_position = led;
		if((count == 100))
		{
			count = 0;
			led = ~led;
			if(i == 10)
			{
				count = 0;
				mode++;
				led = 0x01;
				i = 0;
			}
			else i++;
		}
	}
	else if(mode == 3)
	{
		duty2.Led_position = led2;
		if((count == 100))
		{
			count = 0;
			if(i<3)
			{
				led2 = led1 >> (3-i);
			}
			else led2 = led1 << (i-3);
			i++;
			if(i > 11) i = 0;
		}
	}

}


void Led_dimmer_pattern()
{
	static uint8_t i = 1;
	time1.end = count;
	time2.end = count;
	time1.duration = 2000;
	time2.duration = 2000;
	if(mode == 0)
	{
		led_tmp |= i;
		if(count > 1000)
		{
			duty2.dutyON+= 2;
			count = 0;
			if(i == 0x80) i = 0x01;
			else i <<= 1;
			if(duty2.dutyON > 100)
			{
				duty2.dutyON = 0;
				led_tmp = 0x01;
				i = 0x01;
				mode = 1;
			}
		}		
	}
	else if(mode == 1)
	{
		led_tmp = i;
		if(count > 200)
		{
			duty2.dutyON += 2;
			count = 0;
			if(duty2.dutyON > 100)
			{
				duty2.dutyON = 0;
				if(i == 0x80)
				{
					i = 1;
					led_tmp = 0x01;
					mode = 0;
				}
				else i <<= 1;
			}
		}		
	}
	if((time1.end - time1.start > time1.duration) && (flag1 == 0))
	{
		led_tmp |= i;
		time1.start = count;
		if(flag1 == 0)
		{
			if(i == 0x80) i = 0x01;
			else i <<= 1;
			duty2.dutyON = dosangtb[brightness];
			brightness++;
			if(brightness > 15)
			{
				brightness = 15;
				i = 0xFE;
				flag1 = 1;
				count = 0;
			}
		}
	}
	if((time2.end - time2.start > time2.duration) && (flag1 == 1))
	{
		led_tmp = i;
		time2.start = count;
		if(flag1 == 1)
		{
			i <<= 1;
			duty2.dutyON = dosangtb[brightness];
			if(brightness < 1)
			{
				brightness = 0;
				flag1 = 0;
				i = 0x01;
				led_tmp = 0x01;
				count = 0;
			}
			else brightness--;
		}
	}
}
