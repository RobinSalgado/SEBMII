/*
 * main.h
 *
 *  Created on: 25/10/2017
 *      Author: Oscar
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "KeyboardMenu.h"
#include "LCDNokia5110.h"
#include "LED.h"
#include "stdio.h"
#include "LED.h"
#include "DAC.h"
#include "ADC.h"
#include "PIT.h"
#include "PWM.h"
#include "NVIC.h"
#include "GPIO.h"
#include "SPI.h"
#include "MCG.h"
#include "FlexTimer.h"
#include "Frequency.h"
#include "temperature.h"
#include "Alarm.h"

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

 /**************************************************************************************/

#define HIGH_SPEED_CLOCK
#define SYSTEM_CLOCK 60000000
#define DELAY 0.5F
#define DEBOUNCE 0.05F
#define DELAY_LED 0.5F
#define STRUCTDATA	&strData


#define PRESSED 1
#define RELEASED 0

#define ON 1
#define OFF 0




/********************************************************************************************/
/********************************************************************************************/
/* 							Enum types definitions											*/



typedef enum {
	MASTER_PASS,
	MAIN_SCREEN,
	CHOOSE_FUNCTION,
	ENABLE_FUNCTION,
	FUNCTION_HANDLER,
	DISABLE_FUNCTION
} StateMachine_t;

typedef enum{
	ALARM = 1,
	TEMPERATURE,
	MOTOR,
	MANUAL_OVERRIDE,
	FREQUENCY,
	NEW_PASS
}MenuFunctions_t;


/********************************************************************************************/
/********************************************************************************************/
/* 								Struct types definitions									*/

/**/
typedef struct  {
	uint8 keyboardState;
	uint8 currentState;
	uint32 password[4];
	uint32 newPassword[4];
	uint32 confirmedPassword[4];
	uint32 input;
	sint32 keyboardOutput;
	uint8 i;
	uint8 mainScreen;
	uint8 selectedFunction;
	uint8 enableMenu[7];
}ControlData ;


//Master StateMachine struct

typedef const struct State {
	void (*fptrStateHandler)(ControlData*);
	ControlData* data;
	StateMachine_t next;
} FSM_Generator_t;


/********************************************************************************************/
/********************************************************************************************/
/* 							Global functions declarations									*/

void appInit();
void MasterPass_handler(ControlData* data);
void MainScreen_handler(ControlData * data);
void ChooseFunction_handler(ControlData * data);
void ChooseMenu_handler(ControlData * data);
void SystemBlockCmp(ControlData * data);
void EnableSelectedFunction(ControlData * data);
void Functions_handler(ControlData * data);
void DisableSelectedFunction(ControlData * data);


void SetAlarm(ControlData * data);
void TempFromat(ControlData * data);
void MotorStep(ControlData * data);
void ManualOverride(ControlData * data);
void InputCapture(ControlData * data);
void NewPassword(ControlData* data);




#endif /* MAIN_H_ */
