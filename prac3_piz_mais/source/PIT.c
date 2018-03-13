/*
* PIT.c
 *
 *  Created on: 16/09/2017
 *      Author: dceli
 */

#include "MK64F12.h"
#include "PIT.h"

PIT_interruptFlags_t PIT_intrStatusFlag;

void PIT0_IRQHandler(){
	PIT_intrStatusFlag.flagPIT0 = TRUE;
	PIT_clear(PIT_0);
}

void PIT1_IRQHandler(){
	PIT_intrStatusFlag.flagPIT1 = TRUE;
	PIT_clear(PIT_1);
}

void PIT_delay(PIT_Timer_t pitTimer,float systemClock ,float period){
	PIT->MCR = 0;	//PIT module control register, it enables the PIT timer clocks and allows them to keep working during debud mode.
	float timeVal = ((systemClock * period));				//Module disable = 0 (enable), Freeze = 0 (unfreeze during debugging).
	PIT->CHANNEL[pitTimer].LDVAL = 	(uint32)timeVal - 1;//Timer timeout value.
	PIT->CHANNEL[pitTimer].TCTRL = PIT_TCTRL_TIE_MASK;	//Timer control register, enabling TIE allows the timer interrupts through its flag.
	PIT->CHANNEL[pitTimer].TCTRL |= PIT_TCTRL_TEN_MASK;	//Timer enable.
}

void PIT_clockGating(void){
	SIM->SCGC6 = PIT_CLOCK_GATING;	//0x800000, enabling the PIT bit clock gating.
}

uint8 PIT_getIntrStatus(PIT_Timer_t pitTimer){
	return((PIT->CHANNEL[pitTimer].TFLG && PIT_TFLG_TIF_MASK));	//Comparison. If there is no timer interrupt flag (TIF), it will return 0 (FALSE).
}

void PIT_clear(PIT_Timer_t pitTimer){
	PIT->CHANNEL[pitTimer].TCTRL &= 0;		//To clear the interrupt flag, the timer must be turned off and its interrupt disabled.
	PIT->CHANNEL[pitTimer].TFLG = PIT_TFLG_TIF_MASK;	//Writing 1 in the TIF bit clears the interrupt flag.
	PIT->CHANNEL[pitTimer].TCTRL |= (PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK);	//Timer and its interrupt are reenabled.
}

uint8 PIT_getIRQStatus(PIT_Timer_t pitTimer)
{
	switch (pitTimer) {
		case PIT_0:
			return(PIT_intrStatusFlag.flagPIT0);
			break;
		case PIT_1:
			return(PIT_intrStatusFlag.flagPIT1);
			break;
		case PIT_2:
			return(PIT_intrStatusFlag.flagPIT2);
			break;
		case PIT_3:
			return(PIT_intrStatusFlag.flagPIT3);
			break;
		default:
			return(ERROR);
			break;
	}
}

uint8 PIT_clearIRQStatus(PIT_Timer_t pitTimer)
{
	switch (pitTimer) {
		case PIT_0:
			PIT_intrStatusFlag.flagPIT0 = FALSE;
			break;
		case PIT_1:
			PIT_intrStatusFlag.flagPIT1 = FALSE;
			break;
		case PIT_2:
			PIT_intrStatusFlag.flagPIT2 = FALSE;
			break;
		case PIT_3:
			PIT_intrStatusFlag.flagPIT3 = FALSE;
			break;
		default:
			return(ERROR);
			break;
	}
	return(TRUE);
}
