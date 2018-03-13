/*
 * LC256_driver.c
 *
 *  Created on: 04/11/2017
 *      Author: dceli
 */

#include "LC256_driver.h"

uint8 LC256_writeByte(I2C_Type* I2Cchannel,uint16 address, uint8 byteToWrite){
	uint8 addressLow = address;
	uint8 addressHigh = address >> 8;

	I2C_start(I2Cchannel);			//start
	I2C_writeByte(I2Cchannel, 0xA0);	//Addressing the memory
	I2C_wait(I2Cchannel);				//wait for transmission
	I2C_getACK(I2Cchannel);			//wait for acknowledge
	delay(600);		//Compensate for the missing clock cycle for RX_ACK

	I2C_writeByte(I2Cchannel, addressHigh);	//High address
	I2C_wait(I2Cchannel);
	I2C_getACK(I2Cchannel);
	delay(600);

	I2C_writeByte(I2Cchannel, addressLow);	//Low address
	I2C_wait(I2Cchannel);
	I2C_getACK(I2Cchannel);

	delay(600);

	I2C_writeByte(I2Cchannel, byteToWrite);	//Data to write
	I2C_wait(I2Cchannel);
	I2C_getACK(I2Cchannel);

	delay(600);

	I2C_stop(I2Cchannel);		//Stop signal
	I2C_wait(I2Cchannel);
	I2C_busy(I2Cchannel);		//Wait until the bus is done
	delay(60000);		//Memory write time

	return(TRUE);
}

uint8 LC256_readByte(I2C_Type* I2Cchannel,uint16 address){
	uint8 addressLow = address;
	uint8 addressHigh = address >> 8;
	uint8 retrieved_data;

	I2C_start(I2Cchannel);
	I2C_writeByte(I2Cchannel, 0xA0);
	I2C_wait(I2Cchannel);
	I2C_getACK(I2Cchannel);
	delay(600);

	I2C_writeByte(I2Cchannel, addressHigh);
	I2C_wait(I2Cchannel);
	I2C_getACK(I2Cchannel);
	delay(600);

	I2C_writeByte(I2Cchannel, addressLow);
	I2C_wait(I2Cchannel);
	I2C_getACK(I2Cchannel);
	delay(600);

	I2C_repeatedStart(I2Cchannel);	//Restart for reading
	I2C_writeByte(I2Cchannel, 0xA1);	//Address plus reading bit
	I2C_wait(I2Cchannel);
	I2C_getACK(I2Cchannel);
	delay(600);

	I2C_TXRXMode(I2Cchannel,RECEIVE);	//Switch to receive
	I2C_NACK(I2Cchannel);				//Generate NACK bit
	retrieved_data = I2C_readByte(I2Cchannel);	//Dummy read to generate clock
	I2C_wait(I2Cchannel);
	delay(600);

	I2C_stop(I2Cchannel);		//Stop retrieval
	I2C_wait(I2Cchannel);
	I2C_busy(I2Cchannel);		//wait until bus is clear
	retrieved_data = I2C_readByte(I2Cchannel);	//Get data
	delay(60000);

	return(retrieved_data);
}
