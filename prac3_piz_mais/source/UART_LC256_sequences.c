/*
 * UART_retrieval_conversion.c
 *
 *  Created on: 06/11/2017
 *      Author: dceli
 */

#include "UART_LC256_sequences.h"

extern UART_MailBoxType UART0_MailBox;

uint16 UART_LC256_addressRetrieval(void){
	uint8 addressPosition = 0;	//Auxiliary variable to move through the array
	uint8 addressArray[5] = {};	//Auxiliary array to save the retrieved data
	uint16 address = 0;			//Auxiliary variable to store the calculated address

	UART0_MailBox.mailBox = FALSE;	//Clear the mailbox to avoid the previous enter
	UART0_MailBox.flag = FALSE;		//Clear the flag to appropriately retrieve new data

	while(UART0_MailBox.mailBox != 13){	//Wait until an enter is received
		UART_PITsequence();
	if (UART0_MailBox.flag) {			//If a new data arrives to the mailbox
		//moved flag from bottom to top
		UART0_MailBox.flag = FALSE;		//clear the reception flag
		addressArray[addressPosition] = UART0_MailBox.mailBox;	//retrieve the data and save on the array
		UART_putChar(UART0,addressArray[addressPosition]);		//Echo to the UART
		addressPosition++;			//Move the array pointer
		}
	}
	UART0_MailBox.mailBox = FALSE;	//After the enter is received, clear the mailbox
	UART0_MailBox.flag = FALSE;

	if(addressArray[0] >= 65)	//If the data is A-F, set to its value
		address = (addressArray[0] - '7') * 4096;	//Multiply by 16^3 to set the equivalent value according to the position
	else
		address = (addressArray[0] - '0') * 4096;	//If not, the data is 0-9
	if(addressArray[1] >= 65)
		address += (addressArray[1] - '7') * 256;	//Multiply by 16^2
	else
		address += (addressArray[1] - '0') * 256;
	if(addressArray[2] >= 65)
		address += (addressArray[2] - '7') * 16;	//Multiply by 16^1
	else
		address += (addressArray[2] - '0') * 16;
	if(addressArray[3] >= 65)
		address += addressArray[3] - '7';			//Multiply by 16^0
	else
		address += addressArray[3] - '0';

	return(address);	//Return the calculated address
}

uint16 UART_LC256_lengthRetrieval(void){
	uint8 lengthPosition = 0;	//Auxiliary variable to move through the array
	uint8 lengthArray[3] = {};	//Auxiliary array to save the retrieved data
	uint16 length;				//Auxiliary variable to store the calculated length

	UART0_MailBox.mailBox = FALSE;	//Clear the mailbox to avoid the previous enter
	UART0_MailBox.flag = FALSE;		//Clear the flag to appropriately retrieve new data

	while(UART0_MailBox.mailBox != 13){		//Wait until an enter is received
		UART_PITsequence();
	if (UART0_MailBox.flag) {				//If a new data arrives to the mailbox
		//moved flag from bottom to top
		UART0_MailBox.flag = FALSE;			//clear the reception flag
		lengthArray[lengthPosition] = UART0_MailBox.mailBox;	//retrieve the data and save on the array
		UART_putChar(UART0,lengthArray[lengthPosition]);		//Echo to the UART
		lengthPosition++;	//Move the array pointer
		}
	}
	UART0_MailBox.mailBox = FALSE;	//After the enter is received, clear the mailbox
	UART0_MailBox.flag = FALSE;

	length = (lengthArray[0] - '0') * 10;	//First length data by 10
	length += lengthArray[1] - '0';			//Second as units

	return(length);		//Return length
}

void UART_LC256_dataStorage(uint16 address){
	uint16 dataPosition = 0;		//Auxiliary variable to move through the array
	uint16 saveAux;					//Auxiliary variable for the save sequence
	uint16 saveAddress = address;	//Temporary address to move it
	uint8 dataArray[64] = {};		//Auxiliary array to save the retrieved data

	UART0_MailBox.mailBox = FALSE;	//Clear the mailbox to avoid the previous enter
	UART0_MailBox.flag = FALSE;		//Clear the flag to appropriately retrieve new data

	while(UART0_MailBox.mailBox != 13){		//Wait until an enter is received
		UART_PITsequence();
		if (UART0_MailBox.flag) {			//If a new data arrives to the mailbox
			//moved flag from bottom to top
			UART0_MailBox.flag = FALSE;		//clear the reception flag
			dataArray[dataPosition] = UART0_MailBox.mailBox;	//retrieve the data and save on the array
			UART_putChar(UART0,dataArray[dataPosition]);		//Echo to the UART
			dataPosition++;		//Move the array pointer
		}
	}
	UART0_MailBox.mailBox = FALSE;	//After the enter is received, clear the mailbox
	UART0_MailBox.flag = FALSE;

	for(saveAux = 0;saveAux <= dataPosition; saveAux++){	//Sequence to input the array onto the memory
		LC256_writeByte(I2C0,saveAddress,dataArray[saveAux]);	//Call save function
		saveAddress++;	//Move address
	}

}

void UART_LC256_dataRetrieval(uint16 address, uint16 length){
	uint16 sendAux;		//Auxiliary variable to move through the array for the send sequence
	uint16 readAux;		//Auxiliary variable to move through the array for the retrieval sequence
	uint16 readAddress = address;		//Temporary address to move it
	uint8 dataArray[64] = {};			//Auxiliary array to save the retrieved data

	for(readAux = 0;readAux < length; readAux++){	//Retrieval sequence
		dataArray[readAux] = LC256_readByte(I2C0,readAddress);	//Get data from memory
		readAddress++;		//Move address
	}

	for(sendAux = 0; sendAux < readAux; sendAux++){	//Send sequence
		UART_putChar(UART0,dataArray[sendAux]);		//Send array to the UART
	}
}

void UART_LC256_writeSequence(){
	uint16 auxWriteAddress;		//Variable to store the received address
	UART_putString(UART0, "\033[10;10H");	//<10,10> position on Tera Term
	UART_putString(UART0, "Write address: 0x");	//User interface string
	auxWriteAddress = UART_LC256_addressRetrieval();	//Wait for <data><enter>
	UART_putString(UART0, "\033[11;10H");		//<10,11> position on Tera Term
	UART_putString(UART0, "Data to write: ");	//User interface string
	UART_LC256_dataStorage(auxWriteAddress);			//Data retrieval and storage sequence
}

void UART_LC256_readSequence(){
	uint16 auxReadAddress;	//Variable to store the received address
	uint16 length;			//Variable to store the received length
	UART_putString(UART0, "\033[10;10H");		//<10,10> position on Tera Term
	UART_putString(UART0, "Read address: 0x");	//User interface string
	auxReadAddress = UART_LC256_addressRetrieval();	//Address retrieval sequence
	UART_putString(UART0, "\033[11;10H");		//<10,11> position on Tera Term
	UART_putString(UART0, "Length to read: ");	//User interface string
	length = UART_LC256_lengthRetrieval();			//Length retrieval sequence
	UART_putString(UART0, "\033[12;10H");		//<10,12> position on Tera Term
	UART_putString(UART0, "Read data: ");		//User interface string
	UART_LC256_dataRetrieval(auxReadAddress,length);	//Data output sequence
}

