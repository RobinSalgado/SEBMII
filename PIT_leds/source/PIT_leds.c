/*Robin Salgado de Anda*/
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
#define GET1SECOND ((0x1312CFF)*4)	// 1/20Mhz = 50ns   (1s/50ns)-1= 19,999,999 cycles or 0x1312CFF
/*
 * @brief   Application entry point.
 */

uint32_t sequenceCtrl = 0;
uint8_t bttn2 = 2; // counter for going back to the default state.
uint8_t bttn3 = 2; // counter for going back to the default state.
void LED_sequence1(void) {
	static uint8_t current_state = 0;
	// Toggle Blue LED

	if (0 == current_state) {
		GPIO_WritePinOutput(GPIOB, 22, 1);
		GPIO_WritePinOutput(GPIOB, 21, 0);
		current_state++;
	} else {
		if (1 == current_state) {
			GPIO_WritePinOutput(GPIOB, 21, 1);
			GPIO_WritePinOutput(GPIOE, 26, 0);
			//state = ( 0 == state ) ? 1 : 0;
			current_state++;
		} else {
			if (2 == current_state) {
				GPIO_WritePinOutput(GPIOE, 26, 1);
				GPIO_WritePinOutput(GPIOB, 22, 0);

				current_state = 0;
			}
		}
	}

	/*
	 GPIO_WritePinOutput(GPIOE,26,1);

	 GPIO_WritePinOutput(GPIOB,21,0);
	 GPIO_WritePinOutput(GPIOB,21,1);

	 GPIO_WritePinOutput(GPIOB,22,0);
	 GPIO_WritePinOutput(GPIOB,22,1);
	 */

}
void LED_sequence2(void) {
	static uint8_t current_state2 = 0;
	GPIO_WritePinOutput(GPIOB, 21, 1);
	GPIO_WritePinOutput(GPIOB, 22, 1);
	GPIO_WritePinOutput(GPIOE, 26, 1);
	if (0 == current_state2) {
		GPIO_WritePinOutput(GPIOE, 21, 1);
		GPIO_WritePinOutput(GPIOB, 22, 0);
		current_state2++;
	} else {
		if (1 == current_state2) {
			GPIO_WritePinOutput(GPIOB, 22, 1);
			GPIO_WritePinOutput(GPIOE, 26, 0);
			current_state2++;
		} else {
			if (2 == current_state2) {

				GPIO_WritePinOutput(GPIOB, 26, 1);
				GPIO_WritePinOutput(GPIOB, 21, 0);
				current_state2 = 0;
			}
		}
	}
}

void PIT0_IRQHandler(void) {
	// Clear interrupt
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
	if (0 == sequenceCtrl) {
		LED_sequence1();

	} else {
		LED_sequence2();
		//sequenceCtrl = 0;
	}

}

void PORTA_IRQHandler() {


	PORT_ClearPinsInterruptFlags(PORTA, 1 << 4);


	if(bttn3 % 2 == 0){
	sequenceCtrl = 1;
	}else{
		sequenceCtrl = 0;
	}
bttn3 ++;

}

void PORTC_IRQHandler() {


	PORT_ClearPinsInterruptFlags(PORTC, 1 << 6);
	if(bttn3 % 2 == 0){
PIT_StopTimer(PIT, kPIT_Chnl_0);
	}else{
		PIT_StartTimer(PIT, kPIT_Chnl_0);
	}
bttn3++;
}
int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();

	CLOCK_EnableClock(kCLOCK_Pit0);
	CLOCK_EnableClock(kCLOCK_PortE);
	CLOCK_EnableClock(kCLOCK_PortB);
	CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_PortC);



	port_pin_config_t config_led = { kPORT_PullDisable, kPORT_SlowSlewRate,
			kPORT_PassiveFilterDisable, kPORT_OpenDrainDisable,
			kPORT_LowDriveStrength, kPORT_MuxAsGpio, kPORT_UnlockRegister, };

	gpio_pin_config_t led_config_gpio = { kGPIO_DigitalOutput, 1 };

	port_pin_config_t config_switch = { kPORT_PullDisable, kPORT_SlowSlewRate,
			kPORT_PassiveFilterDisable, kPORT_OpenDrainDisable,
			kPORT_LowDriveStrength, kPORT_MuxAsGpio, kPORT_UnlockRegister };

	PORT_SetPinInterruptConfig(PORTA, 4, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(PORTC, 6, kPORT_InterruptFallingEdge);

	PORT_SetPinConfig(PORTA, 4, &config_switch);
	PORT_SetPinConfig(PORTC, 6, &config_switch);
	gpio_pin_config_t switch_config_gpio = { kGPIO_DigitalInput, 1 };

	GPIO_PinInit(GPIOA, 4, &switch_config_gpio);
	GPIO_PinInit(GPIOC, 6, &switch_config_gpio);


	NVIC_EnableIRQ(PORTA_IRQn);
	NVIC_EnableIRQ(PORTC_IRQn);

	GPIO_PinInit(GPIOB, 21, &led_config_gpio); // Red led
	GPIO_PinInit(GPIOB, 22, &led_config_gpio); // Blue led
	GPIO_PinInit(GPIOE, 26, &led_config_gpio); // Green led

	PORT_SetPinConfig(PORTB, 21, &config_led);
	PORT_SetPinConfig(PORTB, 22, &config_led);
	PORT_SetPinConfig(PORTE, 26, &config_led);

	PIT->MCR = PIT_MCR_FRZ_SHIFT; // turn on the pit

	PIT_StartTimer(PIT, kPIT_Chnl_0);
	PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, GET1SECOND);

	NVIC_EnableIRQ(PIT0_IRQn); // Enable interrupt registers ISER and ICPR

//PIT_StopTimer(PIT, kPIT_Chnl_0); // para el segundo inciso de la tarea que pare el led

// Green led: PTE26 & RED led: PTB21

	/* Force the counter to be placed into memory. */
	volatile static int i = 0;
	// Enter an infinite loop, just incrementing a counter.
	while (1) {
		i++;
	}
	return 0;
}
