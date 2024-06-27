/*
 * _74HC595.h
 *
 * Created: 6/20/24 01:24:05 AM
 *  Author: TuTran
 */ 


#ifndef _74HC595_H_
#define _74HC595_H_

#include "std_type.h"

#define HC595_DDR		DDRF
#define HC595_PORT		PORTF
#define HC595_LATCH		PF2
#define HC595_CLK		PF0
#define HC595_DATA		PF1
#define HC595_OE		PF3

#define HC595_OE_LOW()				(HC595_PORT &= ~(HIGH << HC595_OE))
#define HC595_OE_HIGH()				(HC595_PORT |= (HIGH  << HC595_OE))

#define HC595_DATA_LOW()			(HC595_PORT &= ~(HIGH  << HC595_DATA))
#define HC595_DATA_HIGH()			(HC595_PORT |= (HIGH  << HC595_DATA))

#define HC595_CLK_LOW()				(HC595_PORT &= ~(HIGH  << HC595_CLK))
#define HC595_CLK_HIGH()			(HC595_PORT |= (HIGH  << HC595_CLK))

#define HC595_LATCH_ACTIVE()		(HC595_PORT |= (HIGH  << HC595_LATCH))
#define HC595_LATCH_DEACTIVE()		(HC595_PORT &= ~(HIGH  << HC595_LATCH))

void HC595Init();
void Pulse_Clock();
void Latch595();
void Transmit_HC595(uint8_t data);
void Wait();

#endif /* _74HC595_H_ */