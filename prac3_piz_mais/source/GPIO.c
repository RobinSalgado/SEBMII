/**
	\file
	\brief
		This is the source file for the GPIO device driver for Kinetis K64.
		It contains all the implementation for configuration functions and runtime functions.
		i.e., this is the application programming interface (API) for the GPIO peripheral.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo
	    Interrupts are not implemented in this API implementation.
 */
#include "MK64F12.h"
#include "GPIO.h"

GPIO_interruptFlags_t GPIO_intrStatusFlag;

void PORTA_IRQHandler()
{
	GPIO_intrStatusFlag.flagPortA  = TRUE;
	GPIO_clearInterrupt(GPIO_A);
}

void PORTC_IRQHandler()
{
	GPIO_intrStatusFlag.flagPortC  = TRUE;
	GPIO_clearInterrupt(GPIO_C);

}

uint8 GPIO_getIRQStatus(GPIO_portNameType gpio)
{
	switch (gpio) {
		case GPIO_A:
			return(GPIO_intrStatusFlag.flagPortA);
			break;
		case GPIO_B:
			return(GPIO_intrStatusFlag.flagPortB);
			break;
		case GPIO_C:
			return(GPIO_intrStatusFlag.flagPortC);
			break;
		case GPIO_D:
			return(GPIO_intrStatusFlag.flagPortD);
			break;
		case GPIO_E:
			return(GPIO_intrStatusFlag.flagPortE);
			break;
		default:
			return(ERROR);
			break;
	}

}

uint8 GPIO_clearIRQStatus(GPIO_portNameType gpio)
{
	switch (gpio) {
		case GPIO_A:
			GPIO_intrStatusFlag.flagPortA = FALSE;
			break;
		case GPIO_B:
			GPIO_intrStatusFlag.flagPortB = FALSE;
			break;
		case GPIO_C:
			GPIO_intrStatusFlag.flagPortC = FALSE;
			break;
		case GPIO_D:
			GPIO_intrStatusFlag.flagPortD = FALSE;
			break;
		case GPIO_E:
			GPIO_intrStatusFlag.flagPortE = FALSE;
			break;
		default:
			return(ERROR);
			break;
	}

	return(TRUE);

}

void GPIO_clearInterrupt(GPIO_portNameType portName)
{
	switch(portName)/** Selecting the GPIO for clock enabling*/
	{
		case GPIO_A: /** GPIO A is selected*/
			PORTA->ISFR=0xFFFFFFFF;
			break;
		case GPIO_B: /** GPIO B is selected*/
			PORTB->ISFR=0xFFFFFFFF;
			break;
		case GPIO_C: /** GPIO C is selected*/
			PORTC->ISFR = 0xFFFFFFFF;
			break;
		case GPIO_D: /** GPIO D is selected*/
			PORTD->ISFR=0xFFFFFFFF;
			break;
		default: /** GPIO E is selected*/
			PORTE->ISFR=0xFFFFFFFF;
			break;

	}// end switch
}

uint8 GPIO_clockGating(GPIO_portNameType portName)
{
	switch(portName)/** Selecting the GPIO for clock enabling*/
			{
				case GPIO_A: /** GPIO A is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTA; /** Bit 9 of SIM_SCGC5 is  set*/
					break;
				case GPIO_B: /** GPIO B is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTB; /** Bit 10 of SIM_SCGC5 is set*/
					break;
				case GPIO_C: /** GPIO C is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTC; /** Bit 11 of SIM_SCGC5 is set*/
					break;
				case GPIO_D: /** GPIO D is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTD; /** Bit 12 of SIM_SCGC5 is set*/
					break;
				case GPIO_E: /** GPIO E is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTE; /** Bit 13 of SIM_SCGC5 is set*/
					break;
				default: /**If doesn't exist the option*/
					return(FALSE);
			}// end switch
	/**Successful configuration*/
	return(TRUE);
}// end function

uint8 GPIO_pinControlRegister(GPIO_portNameType portName,uint8 pin,const GPIO_pinControlRegisterType*  pinControlRegister)
{

	switch(portName)
		{
		case GPIO_A:/** GPIO A is selected*/
			PORTA->PCR[pin] = *pinControlRegister;
			break;
		case GPIO_B:/** GPIO B is selected*/
			PORTB->PCR[pin] = *pinControlRegister;
			break;
		case GPIO_C:/** GPIO C is selected*/
			PORTC->PCR[pin] = *pinControlRegister;
			break;
		case GPIO_D:/** GPIO D is selected*/
			PORTD->PCR[pin] = *pinControlRegister;
			break;
		case GPIO_E: /** GPIO E is selected*/
			PORTE->PCR[pin]= *pinControlRegister;
		default:/**If doesn't exist the option*/
			return(FALSE);
		break;
		}
	/**Successful configuration*/
	return(TRUE);
}

void GPIO_PCR(PORT_Type* portName, uint8 pin, uint32 PinValue){
	portName->PCR[pin] = PinValue;
}

void GPIO_writePORT(GPIO_Type * portName, uint32 Data )	{
	portName->PDOR = Data;
}

uint32 GPIO_readPORT(GPIO_Type * portName)	{
	uint32 portValue = portName->PDIR;
	return(portValue);
}

uint8 GPIO_readPIN(GPIO_Type * portName, uint8 pin)	{
	uint32 pinCompare = (portName->PDIR & (TRUE << pin));
	if(FALSE == pinCompare)
		return(FALSE);
	else
		return(TRUE);
}

void GPIO_setPIN(GPIO_Type * portName, uint8 pin)	{
	portName->PSOR = TRUE << pin;
}

void GPIO_clearPIN(GPIO_Type * portName, uint8 pin)	{
	portName->PCOR = TRUE << pin;
}

void GPIO_togglePIN(GPIO_Type * portName, uint8 pin)	{
	portName->PTOR = TRUE << pin;
}

void GPIO_dataDirectionPORT(GPIO_Type * portName ,uint32 direction)	{
	if(TRUE == direction)	{
		portName->PDDR = GPIO_PDDR_PDD_MASK;
	}
	else	{
		portName->PDDR = ~(GPIO_PDDR_PDD_MASK);
	}
}

void GPIO_dataDirectionPIN(GPIO_Type * portName, uint8 State, uint8 pin)	{

	if(TRUE == State){
		portName->PDDR |= TRUE<<pin;
	}
	else{
		portName->PDDR &= ~(TRUE<<pin);
	}

}
