#include "Matrix_Keyboard.h"

volatile uint8_t col_keyboard = 0xE0;

 const uint8_t matrix_keyboard_arr[16] = {
	 0xD7, 0xEE, 0xDE, 0xBE, 0xED, 0xDD, 0xBD, 0xEB, 0xDB, 0xBB, 0x7E, 0x7D, 0x7B, 0xE7, 0xB7, 0x77
	 //0   //1   //2  //3     //4   //5   //6   //7  //8   //9   //A   //B  //C   //*  //#   //D
 };
 
static volatile uint8_t state_button = 0;
static volatile uint8_t i = 0;
static volatile uint8_t number_button = 0xFF;

void Matrix_Keyboard_Init_Pin(uint8_t DDRX, uint8_t PORTX)
{
	DDRx(0x0F, DDRX, INPUT);
	
	DDRx(0xF0, DDRX, OUTPUT);
	
	PORTX = 0xE0;
}

void Scan_Matrix_Keyboard()
{
	PORTA = col_keyboard;
	if(col_keyboard == 0x70) col_keyboard = 0xE0;
	else
	{
		col_keyboard <<= 1;
		col_keyboard = col_keyboard + 0x10;
		col_keyboard &= 0xF0;
	}
}

uint8_t Check_Button_Pressed()
{
	state_button = PINA&0xFF;
	i = 0;
	while(i < 16)
	{
		if(state_button == matrix_keyboard_arr[i])
		{
			number_button = i;
			return number_button;
		}
		number_button = 0xFF;
		i++;
	}		
}
