/*
 * 7_segment.c
 *
 * Created: 3/23/24 01:53:47 PM
 * Author : TuTran
 */ 

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>

void init();
void SEVSEG_putdigit(unsigned char szam, unsigned char digit);
void SEVSEG_putnumber_t();
void beolvas_kiir();
void matrix();
void matrix1();
void SEVSEG_putnumber_1(uint32_t numb);
void led_on();
unsigned char m_button=12;
unsigned char m_button_1=12;
uint8_t row = 0x70;
uint8_t row1[4] = {3,4,5,6};
uint8_t col[3] = {0,1,2};

unsigned char digit[4] = {0};
unsigned char t[4] = {0};
int j = 0;
int i = 1;
uint32_t number = 0;
int flag = 0;
int count = 0;

int main(void)
{
	init();
    while (1) 
    {
		beolvas_kiir();
		
		if(m_button == 10)
		{
			flag = 1;
			number = digit[3]*1000 + digit[2]*100 + digit[1]*10 + digit[0];	
			led_on();
		}
		if(m_button != 10)
		{
			flag = 0;	
			led_off();	
		}
		
		

    }
}

void led_on()
{
						if(flag == 1)
						{
							PORTB |= (1<<PB4);
						}
}
void led_off()
{
	if(flag == 0)
	{
		PORTB &= ~(1<<PB4);
	}
}
void init()
{
	DDRA = 0xFF;
	DDRC = 0xF8;
	DDRB = 0xF0;
	DDRD = 0xF0;
}

void SEVSEG_putdigit(unsigned char szam, unsigned char digit)
{
	if(digit > 3) return;
	if(szam > 9) return;
	
	PORTA = 0x80 | (digit << 4) | szam;
}

void SEVSEG_putnumber_1(uint32_t numb)
{
	t[3] = numb/1000;
	t[2] = numb/100%10;
	t[1] = numb/10%10;
	t[0] = numb%10;
	j = (j+1)%4;
	SEVSEG_putdigit(t[j], j);	
}
void SEVSEG_putnumber_t()
{
	j = (j+1)%4;
	SEVSEG_putdigit(digit[j], j);
}


void matrix()
{
	const unsigned char billtomb[12]= {69, 14, 13, 11, 22, 21, 19, 38, 37, 35, 70, 67};
	unsigned char num, bill;
	
	PORTC = 0x70;
	_delay_ms(5);
	bill = PINC & 0x07;
	num = 0;
	
	while(num < 12)
	{
		if(bill == billtomb[num])
		{
			m_button = num;
			while (PINC == billtomb[num]);
			break;
		}
		else
		{
			m_button = 12;
			num++;
		}
	}
	if(row == 0x40) row = 0x08;
	else row = row << 1;
}

void matrix1()
{
	const unsigned char billtomb[12]= {61, 118, 117, 115, 110, 109, 107, 94, 93, 91, 62, 59};
	unsigned char num, bill;
	PORTC &= ~(1 << PC7);
	PORTC = row;
	_delay_ms(5);
	bill = PINC & 0x7F;
	num = 0;
	
	while(num < 12)
	{
		if(bill == billtomb[num])
		{			
			while (PINC == billtomb[num]);
			m_button = num;
			break;
		}
		else
		{
			m_button = 12;
			num++;
		}
	}	
	if(row == 0x38) row = 0x70;
	else row = ((row << 1) + 0x08) & 0x7F ;
			
}
void beolvas_kiir()
{
	matrix1();
	if(m_button <= 9)
	{
		i = 4;		
		while(i)
		{
			digit[i] = digit[i-1];
			--i;
		}
		digit[0] = m_button;
			
	}
	SEVSEG_putnumber_t();
	
}
