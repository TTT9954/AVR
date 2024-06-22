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
#include "../Inc/main.h"


typedef unsigned long long int UL_INT;		

void millis_init();
void micros_init();

UL_INT millis();
UL_INT micros();



#endif /* MILLIS_H_ */