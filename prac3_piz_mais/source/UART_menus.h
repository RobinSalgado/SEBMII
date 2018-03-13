/*
 * UART_menus.h
 *
 *  Created on: 07/11/2017
 *      Author: dceli
 */

#ifndef UART_MENUS_H_
#define UART_MENUS_H_

#include "UART.h"
#include "UART_RTC_sequences.h"
#include "UART_LC256_sequences.h"
#include "tempFunction.h"
#include "LC256_driver.h"
#include "UART_retrieval_conversion.h"
#include "PIT.h"
#include "RTC.h"

/********************************************************************************************/
/*!
 	 \brief	Sequence to print the main menu and retrieve the next sequence to execute.
 	 \return uint8 selected menu
 */
uint8 UART_mainMenu(void);

/********************************************************************************************/
/*!
 	 \brief	Sequence to call the next sequence selected from the main menu.
 	 \param[in] uint8 selected menu
 	 \return void
 */
void UART_callSequence(uint8 sequenceSelector);


/********************************************************************************************/
/*!
 	 \brief	Sequence to retrieve the data from the memory to return to the UART. It moves through
 	 the memory n-length places from the input address and returns the obtained data.
 	 \param[in] address Memory address where the data is retrieved from.
 	 \param[in] length Number of elements to retrieve from the memory.
 	 \return void
 */
void UARTMenu_readHour();

/********************************************************************************************/
/*!
 	 \brief	Sequence to retrieve the data from the memory to return to the UART. It moves through
 	 the memory n-length places from the input address and returns the obtained data.
 	 \param[in] address Memory address where the data is retrieved from.
 	 \param[in] length Number of elements to retrieve from the memory.
 	 \return void
 */
void UARTMenu_readDate();





#endif /* UART_MENUS_H_ */
