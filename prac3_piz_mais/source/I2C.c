/*
 * I2C.c
 *
 *  Created on: 30/10/2017
 *      Author: dceli
 */

#include "I2C.h"

void I2C0_init(uint32 systemClock, uint16 baudRate){
	GPIO_clockGating(GPIO_B);
//	GPIO_pinControlRegister(GPIO_B,BIT2,(GPIO_MUX2));	//Port B, pin 2 as I2C0_SCL
//	GPIO_pinControlRegister(GPIO_B,BIT3,(GPIO_MUX2));	//Port B, pin 3 as I2C0_SDA
	PORTB->PCR[2] = GPIO_MUX2;
	PORTB->PCR[3] = GPIO_MUX2;
	I2C_clockGating(I2C_0);
	I2C_enable(I2C0);
	I2C_interruptEnable(I2C0);
	I2C_TXRXMode(I2C0,TRANSMIT);
	I2C_MSTOrSLVMode(I2C0,SLAVE);
	I2C0_setBaudRate_100K(I2C0, systemClock, baudRate);
}

void I2C_enable(I2C_Type* I2Cchannel){
	I2Cchannel->C1 |= I2C_C1_IICEN_MASK;
}

void I2C_interruptEnable(I2C_Type* I2Cchannel){
	I2Cchannel->C1 |= I2C_C1_IICIE_MASK;
}

void I2C0_setBaudRate_100K(I2C_Type* I2Cchannel, uint32 systemClock, uint16 baudRate){
	//TODO: baudRate = busClock / (mult*SCLdiv)
	I2Cchannel->F = I2C_F_MULT(2);
	I2Cchannel->F &= ~(I2C_F_ICR_MASK);

	//uint8 valForICR = systemClock/((baudRate * 4));
	//I2Cchannel->F |= I2C_F_ICR(valForICR);
	I2Cchannel->F |= 0x1C;
}

uint8 I2C_clockGating(I2C_ChannelType channel){
	switch(channel){/** Selecting the I2C channel for clock enabling*/
		case I2C_0: /** Channel 0 is selected*/
			SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
			break;
		case I2C_1: /** Channel 1 is selected*/
			SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;
			break;
		case I2C_2: /** Channel 2 is selected*/
			SIM->SCGC1 |= SIM_SCGC1_I2C2_MASK;
			break;
		default: /**If doesn't exist the option*/
			return(FALSE);
	}// end switch
/**Successful configuration*/
	return(TRUE);
}

void I2C_busy(I2C_Type* I2Cchannel){
	while(FALSE != (I2Cchannel->S & I2C_S_BUSY_MASK)){
	}
}

 void I2C_MSTOrSLVMode(I2C_Type* I2Cchannel, uint8 MasterOrSlave){
	 I2Cchannel->C1 &= ~(I2C_C1_MST_MASK);
	 I2Cchannel->C1 |= I2C_C1_MST(MasterOrSlave);
 }

 void I2C_TXRXMode(I2C_Type* I2Cchannel, uint8 ReceiveOrTransmit){
	 I2Cchannel->C1 &= ~(I2C_C1_TX_MASK);
	 I2Cchannel->C1 |= I2C_C1_TX(ReceiveOrTransmit);
 }

 void I2C_NACK(I2C_Type* I2Cchannel){
	 I2Cchannel->C1 |= I2C_C1_TXAK_MASK;
 }

 void I2C_repeatedStart(I2C_Type* I2Cchannel){
	 I2Cchannel->C1 |= I2C_C1_RSTA_MASK;
 }

void I2C_writeByte(I2C_Type* I2Cchannel, uint8 dataToWrite){
	I2Cchannel->D = dataToWrite;
}

uint8  I2C_readByte(I2C_Type* I2Cchannel){
	return(I2Cchannel->D);
}

void I2C_wait(I2C_Type* I2Cchannel){
	while(FALSE == I2Cchannel->S && I2C_S_IICIF_MASK){
	}
	I2Cchannel->S |= I2C_S_IICIF_MASK;
}

void I2C_getACK(I2C_Type* I2Cchannel){
	while(FALSE != (I2Cchannel->S & I2C_S_RXAK_MASK));
}

void I2C_start(I2C_Type* I2Cchannel){
	I2C_TXRXMode(I2Cchannel, TRANSMIT);
	I2C_MSTOrSLVMode(I2Cchannel, MASTER);
}

void I2C_stop(I2C_Type* I2Cchannel){
	I2Cchannel->C1 &= ~(I2C_C1_TXAK_MASK);
	I2C_MSTOrSLVMode(I2Cchannel, SLAVE);
}

