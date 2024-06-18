
#define F_CPU	16000000UL

#include <avr/io.h>

#include  <string.h>
#include "Timer/Timer.h"
#include "Led Matrix/LedMatrix.h"

uint8_t SegmentDigit[4] = {0x01, 0x02, 0x04, 0x08};

uint8_t SegmentNum[10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0xF8, 0x00, 0x10};
	
uint8_t DigitNumb[4] = {0};

TIMER timer0 = {TIMER0, NORMAL_MODE, PRES_64, 5, 0, 0};
	
uint8_t shift = LEFT;

volatile uint16_t count = 0;

void GetDigitNumb(uint16_t number);

void displaySegment(uint8_t digit, uint8_t number);

void displayNumb();

uint32_t StrLength(const char *s);

int main(void)
{
	DDRx(0xFF, DDRA, OUTPUT);

	LedMatrix_Pin_Init();
	Timer_init(&timer0);
	
	char *str = "HELLOWORLD";
	
	uint8_t l = strlen(str);
	uint8_t last_time = count;
	uint8_t last_time1 = count;
	while(1)
	{	
		Display_Character('B');	
		if(count - last_time > 1000)
		{
			last_time = count;
			ShiftRight();
		}
		if(count - last_time1 > 2000)
		{
			last_time1 = count;
			ShiftLeft();
		}		
	}
}


ISR(TIMER0_OVF_vect)
{
	static uint16_t count1 = 0;
	TCNT0 = 5;
	count++;
	scanTime = 1;
	Scan_LedMatrix();
	//TIFR0 |= TOV0;
}


void Segment_Pin_Init()
{
	DDRx(0xFF, DDRK, OUTPUT);
	DDRx(0xFF, DDRF, OUTPUT);
	
	PORTK = 0x00;
	PORTF = 0xFF;
}

void GetDigitNumb(uint16_t number)
{
	static uint8_t i = 3;
	while(number != 0)
	{
		DigitNumb[i] = number % 10;
		number /= 10;
		i--;
	}
}

void displaySegment(uint8_t digit, uint8_t number)
{
	PORTK = SegmentNum[number];
	PORTF |= ~ (0x01 << digit);
}

void displayNumb(uint16_t number)
{
	static uint8_t digit = 0;
	GetDigitNumb(number);
	displaySegment(digit, DigitNumb[digit]);

}
