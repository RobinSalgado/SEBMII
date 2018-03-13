/*
 * tempFunction.c
 *
 *  Created on: 04/11/2017
 *      Author: dceli
 */

#include  "tempFunction.h"

void delay(uint16 delay)
{
	volatile uint16 counter;
	for(counter=delay; counter > 0; counter--);
}

