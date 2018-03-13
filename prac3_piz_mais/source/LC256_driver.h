/*
 * LC256_driver.h
 *
 *  Created on: 04/11/2017
 *      Author: dceli
 */

#ifndef LC256_DRIVER_H_
#define LC256_DRIVER_H_

#include "I2C.h"
#include "tempFunction.h"

uint8 LC256_writeByte(I2C_Type* I2Cchannel,uint16 address, uint8 byteToWrite);
uint8 LC256_readByte(I2C_Type* I2Cchannel,uint16 address);

#endif /* LC256_DRIVER_H_ */
