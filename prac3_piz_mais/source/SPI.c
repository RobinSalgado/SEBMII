/*
 * SPI.c
 *
 *  Created on: 05/10/2017
 *      Author: dceli
 */

#include "MK64F12.h"
#include "SPI.h"

static void SPI_enable(SPI_Type* SPI_channel){	//SPI enable through MDIS in MCR
	SPI_channel->MCR &= ~(SPI_MCR_MDIS_MASK);	//Clear through negated mask
	SPI_channel->MCR |= SPI_MCR_MDIS(0);	//MDIS = 0 to enable clock
}

static void SPI_clk(SPI_ChannelType SPI_channel){	//Clock gating enable for SPI in SIM
	switch(SPI_channel){
	case SPI_0:
		SIM->SCGC6 |= SPI0_CLOCK_GATING;
		break;
	case SPI_1:
		SIM->SCGC6 |= SPI1_CLOCK_GATING;
		break;
	case SPI_2:
		SIM->SCGC3 |= SPI2_CLOCK_GATING;
		break;
	default:
		break;
	}
}

static void SPI_setMaster(SPI_Type* SPI_channel, SPI_MasterType masterOrSlave){	//Master select for SPI in MCR
	SPI_channel->MCR &= ~(SPI_MCR_MSTR_MASK);	//Clear through negated mask
	SPI_channel->MCR |= SPI_MCR_MSTR(masterOrSlave);
}

static void SPI_fIFO(SPI_Type* SPI_channel, SPI_EnableFIFOType enableOrDisable){	//Enable or disable Tx and Rx FIFOs in MCR
	SPI_channel->MCR &= ~(SPI_MCR_DIS_TXF_MASK);	//Clear through negated mask
	SPI_channel->MCR &= ~(SPI_MCR_DIS_RXF_MASK);	//Clear through negated mask
	SPI_channel->MCR |= SPI_MCR_DIS_TXF(enableOrDisable)|SPI_MCR_DIS_RXF(enableOrDisable);
}

static void SPI_clockPolarity(SPI_Type* SPI_channel, SPI_PolarityType cpol){	//Clock polarity select in CTAR
	SPI_channel->CTAR[0] &= ~(SPI_CTAR_CPOL_MASK);	//Clear through negated mask
	SPI_channel->CTAR[0] |= SPI_CTAR_CPOL(cpol);
}

static void SPI_frameSize(SPI_Type* SPI_channel, uint32 frameSize){	//Frame size in CTAR
	SPI_channel->CTAR[0] &= ~(SPI_CTAR_FMSZ_MASK);	//Clear through negated mask
	SPI_channel->CTAR[0] |= frameSize;
}

static void SPI_clockPhase(SPI_Type* SPI_channel, SPI_PhaseType cpha){	//Clock phase select in CTAR
	SPI_channel->CTAR[0] &= ~(SPI_CTAR_CPHA_MASK);	//Clear through negated mask
	SPI_channel->CTAR[0] |= SPI_CTAR_CPHA(cpha);
}

static void SPI_baudRate(SPI_Type* SPI_channel, uint32 baudRate){	//Baud rate select in CTAR
	SPI_channel->CTAR[0] &= ~(SPI_CTAR_BR_MASK);	//Clear through negated mask
	SPI_channel->CTAR[0] |= SPI_CTAR_BR(baudRate);
}

static void SPI_mSBFirst(SPI_Type* SPI_channel, SPI_LSMorMSBType msb){	//MSB or LSB selectin CTAR
	SPI_channel->CTAR[0] &= ~(SPI_CTAR_LSBFE_MASK);	//Clear through negated mask
	SPI_channel->CTAR[0] |= SPI_CTAR_LSBFE(msb);
}

void SPI_startTranference(SPI_Type* SPI_channel){	//Clear HALT flag in MCR
	SPI_channel->MCR &= ~(SPI_MCR_HALT(1));
}

void SPI_stopTranference(SPI_Type* SPI_channel){	//Set HALT flag in MCR
	SPI_channel->MCR |= SPI_MCR_HALT(1);
}

void SPI_sendOneByte(SPI_Type* SPI_channel, uint8 Data){	//Data to transmit
	SPI_channel->PUSHR = Data;
}

void SPI_init(const SPI_ConfigType* SPI_Config_Struct){
	SPI_clk(SPI_Config_Struct->SCGC_SPI_channel);
	GPIO_clockGating(SPI_Config_Struct->GPIOForSPI.GPIO_portName);
	GPIO_pinControlRegister(SPI_Config_Struct->GPIOForSPI.GPIO_portName,SPI_Config_Struct->GPIOForSPI.SPI_Sout,&(SPI_Config_Struct->pinConttrolRegisterPORTD));
	GPIO_pinControlRegister(SPI_Config_Struct->GPIOForSPI.GPIO_portName,SPI_Config_Struct->GPIOForSPI.SPI_clk,&(SPI_Config_Struct->pinConttrolRegisterPORTD));
	SPI_setMaster(SPI_Config_Struct->SPI_Channel,SPI_Config_Struct->SPI_Master);
	SPI_fIFO(SPI_Config_Struct->SPI_Channel,SPI_Config_Struct->SPI_EnableFIFO);
	SPI_enable(SPI_Config_Struct->SPI_Channel);
	SPI_clockPolarity(SPI_Config_Struct->SPI_Channel,SPI_Config_Struct->SPI_Polarity);
	SPI_frameSize(SPI_Config_Struct->SPI_Channel,SPI_Config_Struct->frameSize);
	SPI_clockPhase(SPI_Config_Struct->SPI_Channel,SPI_Config_Struct->SPI_Phase);
	SPI_baudRate(SPI_Config_Struct->SPI_Channel,SPI_Config_Struct->baudrate);
	SPI_mSBFirst(SPI_Config_Struct->SPI_Channel,SPI_Config_Struct->SPI_LSMorMSB);
}

