/*
 * Matrix_Keyboard.h
 *
 * Created: 6/24/24 11:57:44 PM
 *  Author: TuTran
 */ 


#ifndef MATRIX_KEYBOARD_H_
#define MATRIX_KEYBOARD_H_

#include "std_type.h"

extern volatile uint8_t col_keyboard;

extern const uint8_t matrix_keyboard_arr[16];

void Matrix_Keyboard_Init_Pin(uint8_t DDRX, uint8_t PORTX);

void Scan_Matrix_Keyboard();

uint8_t Check_Button_Pressed();




#endif /* MATRIX_KEYBOARD_H_ */