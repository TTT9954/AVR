/*
 * millis.h
 *
 * Created: 5/9/24 02:39:07 PM
 *  Author: TuTran
 */ 


#ifndef MILLIS_H_
#define MILLIS_H_

#include <limits.h>
#include "Timer.h"

#define UUL_INT		unsigned long long int

void millis_init();
void micros_init();

volatile UUL_INT millis();
volatile UUL_INT micros();



#endif /* MILLIS_H_ */