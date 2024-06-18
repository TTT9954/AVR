/*
 * LedMatrix.h
 *
 * Created: 6/16/24 11:53:55 PM
 *  Author: TuTran
 */ 


#ifndef LEDMATRIX_H_
#define LEDMATRIX_H_

#include "../Inc/main.h"
#include <util/delay.h>

enum DIRECTION{
	LEFT,
	RIGHT
};
extern uint8_t colScan[8];

extern uint8_t character[][8];

extern uint8_t Matrix_Pattern;

extern uint8_t Scan_Matrix_Char;

extern uint8_t scanTime;

extern const uint8_t temp_character[26][8];

extern uint8_t Char;

void LedMatrix_Pin_Init();

void Scan_LedMatrix();

void Display_Character(char c);

void Display_String(char *str);

void Shift_LedMatrix(char c);

void ShiftLeft();

void ShiftRight();

void Pattern1();
#endif /* LEDMATRIX_H_ */