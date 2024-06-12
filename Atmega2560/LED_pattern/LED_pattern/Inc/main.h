#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define CLEAR_BIT(REG, BIT)     (REG &= ~(BIT))
#define SET_BIT(REG, BIT)       (REG |= (BIT))

#define ENABLE      1
#define DISBALE     0

#define HIGH		1
#define	LOW			0

#define OUTPUT		1
#define INPUT		0
#endif 