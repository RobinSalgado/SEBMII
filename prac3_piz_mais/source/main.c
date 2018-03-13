/*
 * main.c
 *
 *  Created on: 31/10/2017
 *      Author: dceli
 */

#include "UART_LC256_sequences.h"
#include "MK64F12.h"
#include "MCG.h"
#include "GPIO.h"
#include "I2C.h"
#include "NVIC.h"
#include "UART.h"
#include "SPI.h"
#include "RTC.h"
#include "UART_RTC_sequences.h"
#include "UART_retrieval_conversion.h"

#include "UART_menus.h"

#include "DataTypeDefinitions.h"
#include "LC256_driver.h"
#include "tempFunction.h"

/////////////////////////////////////////////////////////////////////////////////////////////
#include "MCG.h"
#define CLK_FREQ_HZ 50000000  /* CLKIN0 frequency */
#define SLOW_IRC_FREQ 32768	/*This is the approximate value for the slow irc*/
#define FAST_IRC_FREQ 4000000 /*This is the approximate value for the fast irc*/
#define EXTERNAL_CLOCK 0 /*It defines an external clock*/
#define PLL_ENABLE 1 /**PLL is enabled*/
#define PLL_DISABLE 0 /**PLL is disabled*/
#define CRYSTAL_OSC 1  /*It defines an crystal oscillator*/
#define LOW_POWER 0     /* Set the oscillator for low power mode */
#define SLOW_IRC 0 		/* Set the slow IRC */
#define CLK0_TYPE 0     /* Crystal or canned oscillator clock input */
#define PLL0_PRDIV 25    /* PLL predivider value */
#define PLL0_VDIV 30    /* PLL multiplier value*/
/** Macros for debugging*/
#define PLL_DIRECT_INIT
///////////////////////////////////////////////////////////////////////////////////////////////

extern UART_MailBoxType UART0_MailBox;

/** \brief This is the configuration structure to configure the LCD.
 * Note that is constants and it is because is only a variable used for configuration*/
const SPI_ConfigType SPI_Config = { SPI_DISABLE_FIFO, SPI_LOW_POLARITY,
		SPI_LOW_PHASE, SPI_MSB,
		SPI0, SPI_0, SPI_MASTER,
		GPIO_MUX2,
		//SPI_BAUD_RATE_2,
		SPI_BAUD_RATE_4, SPI_FSIZE_8, { GPIO_D, BIT1, BIT2 } };
/*! This array hold the initial picture that is shown in the LCD*/

void appInit();

int main(void) {

	appInit();
	uint8 menuSelector = 0;
	while (1) {
		menuSelector = UART_mainMenu();
		UART_callSequence(menuSelector);
	}

	return 0;
}

void appInit(){
	/*********************************************************************************************
	 * System clock upping to 60 MHz
	 *********************************************************************************************/
	uint32 mcg_clk_hz;
	unsigned char modeMCG = 0;

	mcg_clk_hz = pll_init(CLK_FREQ_HZ, LOW_POWER, EXTERNAL_CLOCK, PLL0_PRDIV,
			PLL0_VDIV, PLL_ENABLE);
	/*********************************************************************************************/
	PIT_clockGating();						//clock gating enable for the PIT

	GPIO_clockGating(GPIO_D);

	SPI_init(&SPI_Config); /*! Configuration function for the LCD port*/
	LCDNokia_init(); /*! Configuration function for the LCD */
	delay(5000);
	LCDNokia_clear();/*! It clears the information printed in the LCD*/
	delay(5000);
	LCDNokia_clear();/*! It clears the information printed in the LCD*/
	LCDNokia_sendString("ITESO");
	delay(5000);
	LCDNokia_clear();/*! It clears the information printed in the LCD*/

	I2C0_init(mcg_clk_hz,100000);
	GPIO_PCR(PORTB, BIT16, GPIO_MUX3);
	GPIO_PCR(PORTB, BIT17, GPIO_MUX3);
	/**Configures UART 0 to transmit/receive at 11520 bauds with a 21 MHz of clock core*/
	UART_init(UART0, UART_0, mcg_clk_hz, BD_115200);
	/**Enables the UART 0 interrupt*/
	UART_interruptEnable(UART0);
	/**Enables the UART 0 interrupt in the NVIC*/
	NVIC_enableInterruptAndPriotity(UART0_IRQ, PRIORITY_1);
	/*VT100 command for clearing the screen*/
	UART_putString(UART0, "\033[2J");
	UART_putString(UART0, "\033[104m");
	NVIC_enableInterruptAndPriotity(PIT_CH0_IRQ, PRIORITY_5); //NVIC priority set and enabling for PIT0
	PIT_delay(PIT_0, mcg_clk_hz, 1);

	RTC_init();

	/**Enables interrupts*/
	EnableInterrupts;
}
