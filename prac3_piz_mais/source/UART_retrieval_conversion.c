/*
 * UART_retrieval_conversion.c
 *
 *  Created on: 06/11/2017
 *      Author: dceli
 */

#include "UART_retrieval_conversion.h"

extern UART_MailBoxType UART0_MailBox;

uint8 GLOBAL_ARRAY [64] = {};

uint8 UART_addressRetrieval(void){
	uint8 addressPosition = 0;
	uint8 addressArray[5] = {};
	uint8 address = 0;

	UART0_MailBox.mailBox = FALSE;
	UART0_MailBox.flag = FALSE;

	//while(addressPosition < 4){
	//for(;addressPosition < 5;){
	while(UART0_MailBox.mailBox != 13){
	if (UART0_MailBox.flag) {
		//moved flag from bottom to top
		UART0_MailBox.flag = FALSE;
		addressArray[addressPosition] = UART0_MailBox.mailBox;
		UART_putChar(UART0,addressArray[addressPosition]);
		addressPosition++;
		}
	}
	UART0_MailBox.mailBox = FALSE;
	UART0_MailBox.flag = FALSE;

	if(addressArray[0] >= 65)
		address = (addressArray[0] - '7') * 4096;
	else
		address = (addressArray[0] - '0') * 4096;
	if(addressArray[1] >= 65)
		address += (addressArray[1] - '7') * 256;
	else
		address += (addressArray[1] - '0') * 256;
	if(addressArray[2] >= 65)
		address += (addressArray[2] - '7') * 16;
	else
		address += (addressArray[2] - '0') * 16;
	if(addressArray[3] >= 65)
		address += addressArray[3] - '7';
	else
		address += addressArray[3] - '0';

	return(address);
}

uint8 UART_lengthRetrieval(void){
	uint8 lengthPosition = 0;
	uint8 lengthArray[2] = {};
	uint8 length;

	UART0_MailBox.mailBox = FALSE;
	UART0_MailBox.flag = FALSE;

	while(UART0_MailBox.mailBox != 13){
	if (UART0_MailBox.flag) {
		//moved flag from bottom to top
		UART0_MailBox.flag = FALSE;
		lengthArray[lengthPosition] = UART0_MailBox.mailBox;
		UART_putChar(UART0,lengthArray[lengthPosition]);
		lengthPosition++;
		}
	}

	UART0_MailBox.mailBox = FALSE;
	UART0_MailBox.flag = FALSE;

	length = (lengthArray[0] - '0') * 10;
	length += lengthArray[1] - '0';

	return(length);
}

void UART_dataStorage(uint8 address){
	uint16 dataPosition = 0;
	uint8 saveAux;
	uint8 saveAddress = address;
	uint8 dataArray[64] = {};

	UART0_MailBox.mailBox = FALSE;
	UART0_MailBox.flag = FALSE;

	while(UART0_MailBox.mailBox != 13){
		if (UART0_MailBox.flag) {
			//moved flag from bottom to top
			UART0_MailBox.flag = FALSE;
			dataArray[dataPosition] = UART0_MailBox.mailBox;
			UART_putChar(UART0,dataArray[dataPosition]);
			dataPosition++;
		}
	}
	UART0_MailBox.mailBox = FALSE;
	UART0_MailBox.flag = FALSE;

	for(saveAux = 0;saveAux <= dataPosition; saveAux++){
		RTC_singleWrite(I2CSLAVE_RTC,saveAddress,dataArray[saveAux]);
		saveAddress++;
	}

//	for(saveAux = 0;saveAux <= dataPosition; saveAux++){
//		GLOBAL_ARRAY[saveAux] = dataArray[saveAux];
//		}

}

void UART_dataRetrieval(uint8 address, uint8 length){
	uint8 sendAux;
	uint8 readAux;
	uint8 readAddress = address;
	uint8 dataArray[64] = {};

	for(readAux = 0;readAux < length; readAux++){
		dataArray[readAux] = RTC_singleRead(I2CSLAVE_RTC,readAddress);
		readAddress++;
	}

	for(sendAux = 0; sendAux < readAux; sendAux++){
		UART_putChar(UART0,dataArray[sendAux]);
	}
/*
	for(sendAux = 0; sendAux < readAux; sendAux++){
			UART_putChar(UART0,GLOBAL_ARRAY[sendAux]);
		}
		*/
}

void UART_writeSequence(){
	uint8 auxWriteAddress;

	UART_putString(UART0, "\033[10;10H");
	UART_putString(UART0, "Write address: 0x");
	auxWriteAddress = UART_addressRetrieval();
	UART_putString(UART0, "\033[11;10H");
	UART_putString(UART0, "Data to write: ");
	UART_dataStorage(auxWriteAddress);
	/************************************
	 * Debugging section
	 ************************************
	UART_putString(UART0, "\033[12;10H");
	UART_dataRetrieval(auxWriteAddress,20);
	/************************************
	 * End of debugging section
	 ************************************/
}

void UART_readSequence(){
	uint8 auxReadAddress;
	uint8 length;
	UART_putString(UART0, "\033[10;10H");
	UART_putString(UART0, "Read address: 0x");
	auxReadAddress = UART_addressRetrieval();
	UART_putString(UART0, "\033[11;10H");
	UART_putString(UART0, "Length to read: ");
	length = UART_lengthRetrieval();
	UART_putString(UART0, "\033[12;10H");
	UART_putString(UART0, "Read data: ");
	UART_dataRetrieval(auxReadAddress,length);
}

