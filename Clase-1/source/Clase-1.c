/*
 * Copyright (c) 2017, NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    Clase-1.c
 * @brief   Application entry point.
 */
#include "fsl_gpio.h"
#include "fsl_port.h"
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */

/*void PORTA_IRQHandler() // esta función la encontramos en el startup
{
PORT_ClearPinsInterruptFlags (PORTA, leds);
static void GPIO_WritePinOutput ( PORTA, uint32_t pin, uint8_t output );
state = (0 = state ) ? 1: 0;
}*/


int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
	CLOCK_EnableClock(kCLOCK_PortB);
	CLOCK_EnableClock(kCLOCK_PortA);
	//falta el clock

	/* Input pin PORT configuration*/
	port_pin_config_t config = {
			kPORT_PullDisable,
			kPORT_SlowSlewRate, // pendiente más alta posible, entre más alta la pendiente más consumo de potencia
			kPORT_PassiveFilterDisable,
			kPORT_OpenDrainDisable,
			kPORT_LowDriveStrength, // que tanta corriente queremos sacar por ese pin
			kPORT_MuxAsGpio,
			kPORT_UnlockRegister, };
	/* Sets the configuration*/
	PORT_SetPinConfig(PORTB, 21, &config);

	/* Output pin configuration*/
	 gpio_pin_config_t led_config =
	 {
	 kGPIO_DigitalOutput,
	 0,
	 };

	 /* Input pin PORT configuration*/
	 	port_pin_config_t configPushBttn= {
	 			kPORT_PullDisable,
	 			kPORT_SlowSlewRate, // pendiente más alta posible, entre más alta la pendiente más consumo de potencia
	 			kPORT_PassiveFilterDisable,
	 			kPORT_OpenDrainDisable,
	 			kPORT_LowDriveStrength, // que tanta corriente queremos sacar por ese pin
	 			kPORT_MuxAsGpio,
	 			kPORT_UnlockRegister, };
	 	/* Sets the configuration*/
	 	PORT_SetPinConfig(PORTB, 21, &config);

	 	/* Output pin configuration*/
	 	 gpio_pin_config_t PushBttn_config =
	 	 {
	 	 kGPIO_DigitalOutput,
	 	 1,
	 	 };
	 /* Sets the configuration*/
	 GPIO_PinInit(GPIOB, 21, &led_config);

	 NVIC_EnableIRQ(PORTA_IRQn);

		//static void GPIO_WritePinOutput ( GPIO_Type *base, uint32_t pin, uint8_t output );
	 /* Force the counter to be placed into memory. que no esté en el stack*/
	//  volatile static int i = 0 ;
	/* Enter an infinite loop, just incrementing a counter. */
	while (1) {
		PRINTF("HOLA MUNDO");

		// i++ ;
	}
	return 0;
}
