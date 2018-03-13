/*
 * UART_menus.c
 *
 *  Created on: 07/11/2017
 *      Author: dceli, omaiste
 */

#include "UART_menus.h"
extern UART_MailBoxType UART0_MailBox;

uint8 UART_mainMenu(void) {
	uint8 jumpToMenu;
	//Main menu with Tera Term position commands
	UART_putString(UART0, "\033[2J");
	UART_putString(UART0, "\033[10;10H");
	UART_putString(UART0, "1) Read memory");
	UART_putString(UART0, "\033[11;10H");
	UART_putString(UART0, "2) Write memory");
	UART_putString(UART0, "\033[12;10H");
	UART_putString(UART0, "3) Define hour");
	UART_putString(UART0, "\033[13;10H");
	UART_putString(UART0, "4) Define date");
	UART_putString(UART0, "\033[14;10H");
	UART_putString(UART0, "5) Hour format");
	UART_putString(UART0, "\033[15;10H");
	UART_putString(UART0, "6) Read hour");
	UART_putString(UART0, "\033[16;10H");
	UART_putString(UART0, "7) Read date");
	//Wait for a menu selection
	while (!UART0_MailBox.flag) {
		UART_PITsequence();
	}
	jumpToMenu = UART0_MailBox.mailBox;
	UART0_MailBox.mailBox = FALSE;
	UART0_MailBox.flag = FALSE;
	return (jumpToMenu);
}

void UART_callSequence(uint8 sequenceSelector) {
	UART_putString(UART0, "\033[2J");
	//Menu sequence selector
	switch (sequenceSelector) {
	case '1':
		UART_putString(UART0, "\033[2J");
		UART_LC256_readSequence();
		break;
	case '2':
		UART_putString(UART0, "\033[2J");
		UART_LC256_writeSequence();
		break;
	case '3':
		UART_putString(UART0, "\033[2J");
		UART_RTC_setHourSequence();
		break;
	case '4':
		UART_putString(UART0, "\033[2J");
		UART_RTC_setDateSequence();
		break;
	case '5':

		UART_putString(UART0, "\033[2J");
		UART_RTC_formatSequence();
		break;
	case '6':
		UART_putString(UART0, "\033[2J");
		UART_RTC_readHourSequence();
		break;
	case '7':
		UART_putString(UART0, "\033[2J");
		UART_RTC_readDateSequence();
		break;;
	default:
		break;
	}
	//Wait for <esc> to return to main menu after a sequence.
	while (UART0_MailBox.mailBox != 27) {
		UART_PITsequence();
	}
	UART0_MailBox.flag = FALSE;
}
