/*
 * UART_retrieval_conversion.h
 *
 *  Created on: 06/11/2017
 *      Author: dceli
 */

#ifndef UART_RETRIEVAL_CONVERSION_H_
#define UART_RETRIEVAL_CONVERSION_H_

#include "UART.h"
#include "tempFunction.h"
#include "LC256_driver.h"
#include "RTC.h"

uint8 UART_addressRetrieval(void);
uint8 UART_lengthRetrieval(void);
void UART_dataStorage(uint8 address);
void UART_dataRetrieval(uint8 address, uint8 length);
void UART_writeSequence(void);
void UART_readSequence(void);

#endif /* UART_RETRIEVAL_CONVERSION_H_ */
