#ifndef LEDMATRIX_H_
#define LEDMATRIX_H_

#include "E:\AVR\Atmega2560\Lib\std_type.h"


enum DIRECTION{
	LEFT,
	RIGHT
};
extern u8 colScan[8];

extern u8 character[][8];

extern u8 Matrix_Pattern;

extern u8 Scan_Matrix_Char;

extern u8 scanTime;

extern const u8 temp_character[27][8];

extern u8 Char;

void LedMatrix_Pin_Init();

void Scan_LedMatrix();

void Display_Character(char c);

void Display_String(char *str);

void Shift_LedMatrix(u8 mode, u32 speed);

void ShiftLeft(u32 speed);

void ShiftRight(u32 speed);

void Pattern1();
#endif /* LEDMATRIX_H_ */