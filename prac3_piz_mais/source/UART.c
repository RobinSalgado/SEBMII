/*
 /*
 * UART.c
 *
 *  Created on: 10/10/2017
 *      Author: Oscar
 */
#include "UART.h"
UART_MailBoxType UART0_MailBox;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This is the interrupt services routing (ISR).
 \param[in]  void.
 \return void
 */
void UART0_RX_TX_IRQHandler(void) {

	while (!(UART0->S1 & UART_S1_RDRF_MASK));
	UART0_MailBox.mailBox = UART0->D;
	UART0_MailBox.flag = TRUE;

}

//
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/

void UART_init(UART_Type* uartChannel, UART_ChannelType SCGCuartChannel,
		uint32 systemClk, UART_BaudRateType baudRate) {

	//Auxiliary variables for necessary variables
	uint16 uartSBR = systemClk / (16 * baudRate);
	uint16 uartBRFD = systemClk / (baudRate) - 16 * uartSBR;
	uint16 uartSBRH = uartSBR >> 8;
	uint16 uartBRFA = uartBRFD * 32;

	//UART clock gating
	UART_clockGating(SCGCuartChannel);

	//Disable the receiver and transmitter
	uartChannel->C2 &= ~(UART_C2_RE_MASK);
	uartChannel->C2 &= ~(UART_C2_TE_MASK);

	//Baud rate into its registers
	uartChannel->BDH = uartSBRH;
	uartChannel->BDL = uartSBR;

	//Clear BRFA and include the calculated value
	uartChannel->C4 &= ~(UART_C4_BRFA_MASK);
	uartChannel->C4 |= (UART_C4_BRFA_MASK && uartBRFA);

	//Enable transmitter and reciever
	uartChannel->C2 |= UART_C2_RE(TRUE);
	uartChannel->C2 |= UART_C2_TE(TRUE);

	//TXFE and RXFE enable the FIFOs
	//Size set to 64 data words
	//uartChannel->PFIFO = UART_PFIFO_TXFE_MASK | UART_PFIFO_TXFIFOSIZE(6) | UART_PFIFO_RXFE_MASK | UART_PFIFO_RXFIFOSIZE(6);
}

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 enables the RX UART interrupt). This function should include the next sentence:
 while (!(UART0_S1 & UART_S1_RDRF_MASK)). It is to guaranty that the incoming data is complete
 when reception register is read. For more details see chapter 52 in the kinetis reference manual.
 \param[in]  uartChannel indicates the UART channel.
 \return void
 */
void UART_interruptEnable(UART_Type* uartChannel) {


//	while (!(uartChannel->S1 & UART_S1_RDRF_MASK));
	UART0->C2 |= UART_C2_RIE_MASK;
}

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/

void UART_clockGating(UART_ChannelType SCGCuartChannel) {
	switch (SCGCuartChannel) {
	case (UART_0):
		SIM->SCGC4 |= SIM_SCGC4_UART0(TRUE);
		break;
	case (UART_1):
		SIM->SCGC4 |= SIM_SCGC4_UART1(TRUE);
		break;
	case (UART_2):
		SIM->SCGC4 |= SIM_SCGC4_UART2(TRUE);
		break;
	case (UART_3):
		SIM->SCGC4 |= SIM_SCGC4_UART3(TRUE);
		break;
	case (UART_4):
		SIM->SCGC1 |= SIM_SCGC1_UART4(TRUE);
		break;
	case (UART_5):
		SIM->SCGC1 |= SIM_SCGC1_UART5(TRUE);
		break;
	default:
		return;
	}
}
/*!
 \brief	 It sends one character through the serial port. This function should include the next sentence:
 while(!(UART0_S1 & UART_S1_TC_MASK)). It is to guaranty that before to try to transmit a byte, the previous
 one was transmitted. In other word, to avoid to transmit data while the UART is busy transmitting information.
 \param[in]  uartChannel indicates the UART channel.
 \param[in]  character to be transmitted.
 \return void
 */

void UART_putChar(UART_Type* uartChannel, uint8 character) {
	while (!(uartChannel->S1 && UART_S1_TDRE_MASK));
	UART0->D = character;
	delay(1800);
}

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 It sends a string character through the serial port.
 \param[in]  uartChannel indicates the UART channel.
 \param[in]  string pointer to the string to be transmitted.
 \return void
 */
void UART_putString(UART_Type* uartChannel, sint8* string) {
	uint8 i = 0;

	while( string[i] !=	'\0' ){
		UART_putChar( uartChannel, string[i]);
		i++;
	}

}

uint8 UART_PITsequence();
