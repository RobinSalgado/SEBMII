/*
 * UART_RTC_sequences.h
 *
 *  Created on: 09/11/2017
 *      Author: Oscar
 */

#ifndef UART_RTC_SEQUENCES_H_
#define UART_RTC_SEQUENCES_H_

#include "UART.h"
#include "UART_menus.h"
#include "tempFunction.h"
#include "DataTypeDefinitions.h"
#include "RTC.h"



/********************************************************************************************/
/*!
 	 \brief	Sequence to retrieve the address from the UART. It waits for the user inputs and
 	 converts it into the equivalent HEX address.
 	 \return uint8 address
 */
uint8 UART_RTCaddressRetrieval(void);

/********************************************************************************************/
/*!
 	 \brief	Sequence to retrieve the length from the UART. It waits for the user inputs and
 	 converts it into the equivalent HEX address.
 	 \return uint8 length
 */
uint8 UART_RTClengthRetrieval(void);

/********************************************************************************************/
/*!
 	 \brief	Sequence to retrieve the data from the UART to save on the memory. It waits for
 	 the user inputs and calls for the memory input function.
 	 \param[in] address Memory address where the data is saved.
 	 \return void
 */
void UART_RTCdataStorage(uint8 address);

void UART_RTC_readHourSequence() ;

void UART_RTC_readDateSequence() ;

void UART_RTC_hourStorage();

void UART_RTC_dateStorage();

void UART_RTC_setHourSequence();

void UART_RTC_setDateSequence();

void UART_RTC_setWeekdaySequence();

uint8 UART_PITsequence();

void UART_RTC_formatSequence();

void UART_printWeekday(RTC_timeUnion_t time[]);



#endif /* UART_RTC_SEQUENCES_H_ */
