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
 * @file    MK64FN1M0xxx12_Project.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "fsl_pit.h"
#include "fsl_port.h"

/* TODO: insert other definitions and declarations here. */
#define GET1SECOND 0x1312CFF	// 1/20Mhz = 50ns   (1s/50ns)-1= 19,999,999 cycles or 0x1312CFF
/*
 * @brief   Application entry point.
 */

void PIT0_IRQHandler(void){
	// Clear interrupt
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
	static uint8_t state = 0;

		// Toggle Blue LED
GPIO_WritePinOutput(GPIOB,21,state);
state = ( 0 == state ) ? 1 : 0;


}
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();


CLOCK_EnableClock(kCLOCK_Pit0);

PIT->MCR = PIT_MCR_FRZ_SHIFT; // turn on the pit

PIT_StartTimer(PIT, kPIT_Chnl_0);
PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, GET1SECOND);

NVIC_EnableIRQ(PIT0_IRQn);// Enable interrupt registers ISER and ICPR





port_pin_config_t config_led =
 	{ kPORT_PullDisable, kPORT_SlowSlewRate, kPORT_PassiveFilterDisable,
 		kPORT_OpenDrainDisable, kPORT_LowDriveStrength, kPORT_MuxAsGpio,
 			kPORT_UnlockRegister, };

gpio_pin_config_t led_config_gpio =
 { kGPIO_DigitalOutput, 1 };

 	GPIO_PinInit(GPIOB, 21, &led_config_gpio);
 	PORT_SetPinConfig(PORTB, 21, &config_led);

//PIT_StopTimer(PIT, kPIT_Chnl_0); // para el segundo inciso de la tarea que pare el led






    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
   // Enter an infinite loop, just incrementing a counter.
    while(1) {
        i++ ;
    }
    return 0 ;
}
