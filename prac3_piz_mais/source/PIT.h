/*
 * PIT.h
 *
 *  Created on: 16/08/2017
 *      Author: jlpe
 */

#ifndef PIT_H_
#define PIT_H_

#include "DataTypeDefinitions.h"

#define PIT_CLOCK_GATING 0x800000
#define ERROR 0x02

/*! This enumerated constant are used to select the PIT to be used*/
typedef enum {PIT_0,PIT_1,PIT_2,PIT_3} PIT_Timer_t;

typedef struct{
	uint8 flagPIT0: 1;
	uint8 flagPIT1: 1;
	uint8 flagPIT2: 1;
	uint8 flagPIT3: 1;
}PIT_interruptFlags_t;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function handles the PIT0 interrupt operation
 	 \return void
 */
void PIT0_IRQHandler(void);

/*!
 	 \brief	 This function handles the PIT1 interrupt operation
 	 \return void
 */
void PIT0_IRQHandler(void);

/*!
 	 \brief	 This function configures the PIT to generate a delay based on the system clock.
 	 Internally, it enables the PIT module.
 	 \param[in]  pitTimer PIT Timer to be set.
 	 \param[in]  systemClock Base system period.
 	 \param[in]  period Desired period.
 	 \return void
 */
void PIT_delay(PIT_Timer_t pitTimer,float systemClock ,float period);


/*!
 	 \brief	 This function enables the PIT clock gating.
 	 \return void
 */
void PIT_clockGating(void);

/*!
 	 \brief	 This function checks and returns the PIT interrupt flag.
 	  	 \param[in]  pitTimer PIT Timer to obtain its interrupt flag.
 	 \return void
 */
uint8 PIT_getIntrStatus(PIT_Timer_t pitTimer);

/*!
 	 \brief	 This function clears the PIT interrupt flag.
 	 It requires to turn off the PIT.
 	  	 \param[in]  pitTimer PIT Timer to be cleared.
 	 \return void
 */
void PIT_clear(PIT_Timer_t pitTimer);

/*!
 	 \brief	 This function gets the PIT IRQ status flag.
 	  	 \param[in]  pitTimer PIT Timer flag to be checked.
 	 \return void
 */
uint8 PIT_getIRQStatus(PIT_Timer_t pitTimer);

/*!
 	 \brief	 This function clears the PIT IRQ status flag.
 	  	 \param[in]  pitTimer PIT Timer flag to be cleared.
 	 \return void
 */
uint8 PIT_clearIRQStatus(PIT_Timer_t pitTimer);

#endif /* PIT_H_ */
