/*
 * UART_retrieval_conversion.h
 *
 *  Created on: 06/11/2017
 *      Author: dceli
 */

#ifndef UART_LC256_SEQUENCES_H_
#define UART_LC256_SEQUENCES_H_

#include "UART.h"
#include "UART_RTC_sequences.h"
#include "tempFunction.h"
#include "LC256_driver.h"

/********************************************************************************************/
/*!
 	 \brief	Sequence to retrieve the address from the UART. It waits for the user inputs and
 	 converts it into the equivalent HEX address.
 	 \return uint16 address
 */
uint16 UART_LC256_addressRetrieval(void);

/********************************************************************************************/
/*!
 	 \brief	Sequence to retrieve the length from the UART. It waits for the user inputs and
 	 converts it into the equivalent HEX address.
 	 \return uint16 length
 */
uint16 UART_LC256_lengthRetrieval(void);

/********************************************************************************************/
/*!
 	 \brief	Sequence to retrieve the data from the UART to save on the memory. It waits for
 	 the user inputs and calls for the memory input function.
 	 \param[in] address Memory address where the data is saved.
 	 \return void
 */
void UART_LC256_dataStorage(uint16 address);

/********************************************************************************************/
/*!
 	 \brief	Sequence to retrieve the data from the memory to return to the UART. It moves through
 	 the memory n-length places from the input address and returns the obtained data.
 	 \param[in] address Memory address where the data is retrieved from.
 	 \param[in] length Number of elements to retrieve from the memory.
 	 \return void
 */
void UART_LC256_dataRetrieval(uint16 address, uint16 length);

/********************************************************************************************/
/*!
 	 \brief	Full sequence to interact with the user UART to write onto the memory.
 	 \return void
 */
void UART_LC256_writeSequence(void);

/********************************************************************************************/
/*!
 	 \brief	Full sequence to interact with the user UART to read from the memory.
 	 \return void
 */
void UART_LC256_readSequence(void);

#endif /* UART_LC256_SEQUENCES_H_ */
