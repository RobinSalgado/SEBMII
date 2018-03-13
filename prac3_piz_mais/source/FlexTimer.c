/*
 * FlexTimer.c
 *
 *  Created on: 20/10/2017
 *      Author: dceli
 */

#include "FlexTimer.h"

FTM_interruptFlags_t FTM_interrupt_flag;
FTM_channelInterruptFlags_t FTM0_channel_interrupt_flag;
uint32 iniVal = 0;
uint32 finVal = 0;

void FTM0_IRQHandler(void){
	/*
	if(FALSE != (FTM0->SC && FTM_SC_TOF_MASK)){
		FTM_interrupt_flag.flagFTM0 = TRUE;
		FTM_clearOverflowFlag(FTM0);
	}
	if(FALSE != (FTM0->CONTROLS[6].CnSC && FTM_CnSC_CHF_MASK)){
		FTM0_channel_interrupt_flag.flagCH6 = TRUE;
		FTM_clearChannelFlag(FTM0,CHANNEL6);
	}
	*/
	iniVal = finVal;
	finVal = FTM_getChannelValue(FTM0,CHANNEL6);
	FTM_clearChannelFlag(FTM0,CHANNEL6);
}

/***********************************************************+
 * WARNING: SPECIFIC FUNCTIONS FOR INPUT CAPTURE
 */

uint32 GETiniVal(void){
	return(iniVal);
}

uint32 GETfinVal(void){
	return(finVal);
}

/************************************************************/

void FTM1_IRQHandler(void){
	FTM_interrupt_flag.flagFTM1 = TRUE;
	FTM_clearOverflowFlag(FTM1);
}

void FTM_clockGating(CG_FTM_selector_t CG_FTM){
	switch(CG_FTM){
	case FTM_0:
		SIM->SCGC6 |= SIM_SCGC6_FTM0_MASK;
		break;
	case FTM_1:
		SIM->SCGC6 |= SIM_SCGC6_FTM1_MASK;
		break;
	case FTM_2:
		SIM->SCGC6 |= SIM_SCGC6_FTM2_MASK;	//WARNING: There are 2 different clock gating bits for FTM2
		break;
	case FTM_3:
		SIM->SCGC3 |= SIM_SCGC3_FTM3_MASK;
		break;
	default:
		break;
	}
}

uint8 FTM_getIRQStatus(CG_FTM_selector_t FTM)
{
	switch (FTM) {
		case FTM_0:
			return(FTM_interrupt_flag.flagFTM0);
			break;
		case FTM_1:
			return(FTM_interrupt_flag.flagFTM1);
			break;
		case FTM_2:
			return(FTM_interrupt_flag.flagFTM2);
			break;
		case FTM_3:
			return(FTM_interrupt_flag.flagFTM3);
			break;
		default:
			return(ERROR);
			break;
	}
}

uint8 FTM0_getChannelIRQStatus(FTMchannel_t Channel)
{
	switch (Channel) {
		case CHANNEL0:
			return(FTM0_channel_interrupt_flag.flagCH0);
			break;
		case CHANNEL1:
			return(FTM0_channel_interrupt_flag.flagCH1);
			break;
		case CHANNEL2:
			return(FTM0_channel_interrupt_flag.flagCH2);
			break;
		case CHANNEL3:
			return(FTM0_channel_interrupt_flag.flagCH3);
			break;
		case CHANNEL4:
			return(FTM0_channel_interrupt_flag.flagCH4);
			break;
		case CHANNEL5:
			return(FTM0_channel_interrupt_flag.flagCH5);
			break;
		case CHANNEL6:
			return(FTM0_channel_interrupt_flag.flagCH6);
			break;
		case CHANNEL7:
			return(FTM0_channel_interrupt_flag.flagCH7);
			break;
		default:
			return(ERROR);
			break;
	}
}

uint8 FTM_clearIRQStatus(CG_FTM_selector_t FTM)
{
	switch (FTM) {
		case FTM_0:
			FTM_interrupt_flag.flagFTM0 = FALSE;
			break;
		case FTM_1:
			FTM_interrupt_flag.flagFTM1 = FALSE;
			break;
		case FTM_2:
			FTM_interrupt_flag.flagFTM2 = FALSE;
			break;
		case FTM_3:
			FTM_interrupt_flag.flagFTM3 = FALSE;
			break;
		default:
			return(ERROR);
			break;
	}
	return(TRUE);
}

uint8 FTM0_clearChannelIRQStatus(uint8 Channel)
{
	switch (Channel) {
		case CHANNEL0:
			FTM0_channel_interrupt_flag.flagCH0 = FALSE;
			break;
		case CHANNEL1:
			FTM0_channel_interrupt_flag.flagCH1 = FALSE;
			break;
		case CHANNEL2:
			FTM0_channel_interrupt_flag.flagCH2 = FALSE;
			break;
		case CHANNEL3:
			FTM0_channel_interrupt_flag.flagCH3 = FALSE;
			break;
		case CHANNEL4:
			FTM0_channel_interrupt_flag.flagCH4 = FALSE;
			break;
		case CHANNEL5:
			FTM0_channel_interrupt_flag.flagCH5 = FALSE;
			break;
		case CHANNEL6:
			FTM0_channel_interrupt_flag.flagCH6 = FALSE;
			break;
		case CHANNEL7:
			FTM0_channel_interrupt_flag.flagCH7 = FALSE;
			break;
		default:
			return(ERROR);
			break;
	}
	return(TRUE);
}

void FTM_writeProtectionEnable(FTM_Type * FTM, enableOrDisable_t FTM_writeProtectionEnable){
	FTM->MODE &= ~(FTM_MODE_WPDIS_MASK);
	FTM->MODE |= FTM_MODE_WPDIS(FTM_writeProtectionEnable);
}

void FTM_modulo(FTM_Type * FTM, uint16 moduloValue){
	FTM->MOD = moduloValue;
}

void FTM_clockSourceSelect(FTM_Type * FTM, clockSource_t clockSelector){
	FTM->SC &= ~(FTM_SC_CLKS_MASK);
	FTM->SC |= FTM_SC_CLKS(clockSelector);
}

void FTM_prescalerSelect(FTM_Type * FTM, prescalerFactor_t prescalerSelector){
	FTM->SC &= ~(FTM_SC_PS_MASK);
	FTM->SC |= FTM_SC_PS(prescalerSelector);
}

void FTM_enableInterrupt(FTM_Type * FTM, enableOrDisable_t interruptEnable){
	FTM->SC &= ~(FTM_SC_TOIE_MASK);
	FTM->SC |= FTM_SC_TOIE(interruptEnable);
}

void FTM_enableChannelInterrupt(FTM_Type * FTM, uint8 FTMchannel, enableOrDisable_t channelInterruptEnable){
	FTM->CONTROLS[FTMchannel].CnSC &= ~(FTM_CnSC_CHIE_MASK);
	FTM->CONTROLS[FTMchannel].CnSC |= FTM_CnSC_CHIE(channelInterruptEnable);
}

void FTM_enableRegisterWrite(FTM_Type * FTM, enableOrDisable_t registerWriteEnable){
	FTM->MODE &= ~(FTM_MODE_FTMEN_MASK);
	FTM->MODE |= FTM_MODE_FTMEN(registerWriteEnable);
}

void FTM_channelStatusAndControl(FTM_Type * FTM, uint8 FTMchannel, CSCbits_t CSCselector){
	FTM->CONTROLS[FTMchannel].CnSC &= ~(FTM_CnSC_MSA_MASK);
	FTM->CONTROLS[FTMchannel].CnSC &= ~(FTM_CnSC_MSB_MASK);
	FTM->CONTROLS[FTMchannel].CnSC &= ~(FTM_CnSC_ELSA_MASK);
	FTM->CONTROLS[FTMchannel].CnSC &= ~(FTM_CnSC_ELSB_MASK);
	FTM->CONTROLS[FTMchannel].CnSC |= FTM_CnSC_MSA(CSCselector.MSA)|FTM_CnSC_MSB(CSCselector.MSB);
	FTM->CONTROLS[FTMchannel].CnSC |= FTM_CnSC_ELSA(CSCselector.ELSA)|FTM_CnSC_ELSB(CSCselector.ELSB);
}

void FTM_setChannelValue(FTM_Type * FTM, uint8 FTMchannel, uint16 FTMchannelValue){
	FTM->CONTROLS[FTMchannel].CnV = FTMchannelValue;
}

uint16 FTM_getChannelValue(FTM_Type * FTM, uint8 FTMchannel){
	return(FTM->CONTROLS[FTMchannel].CnV);
}

void FTM_clearOverflowFlag(FTM_Type * FTM){
	FTM->SC &= ~(FTM_SC_TOF_MASK);
}

void FTM_clearChannelFlag(FTM_Type * FTM, uint8 FTMchannel){
	FTM->CONTROLS[FTMchannel].CnSC &= ~(FTM_CnSC_CHF_MASK);
}

void FTM_BDMmode(FTM_Type * FTM, BDMmode_t BDMselector){
	FTM->CONF &= ~(FTM_CONF_BDMMODE_MASK);
	FTM->CONF |= FTM_CONF_BDMMODE(BDMselector);
}

void FTM_init(FTM_init_config_t FTM_config_struct){
	FTM_clockGating(FTM_config_struct.CG_FTM);
	FTM_writeProtectionEnable(FTM_config_struct.FTM, FTM_config_struct.FTM_writeProtectionEnable);
	FTM_enableRegisterWrite(FTM_config_struct.FTM, FTM_config_struct.registerWriteEnable);
	FTM_modulo(FTM_config_struct.FTM, FTM_config_struct.moduloValue);
	FTM_clockSourceSelect(FTM_config_struct.FTM, FTM_config_struct.clockSelector);
	FTM_prescalerSelect(FTM_config_struct.FTM, FTM_config_struct.prescalerSelector);
	FTM_enableInterrupt(FTM_config_struct.FTM, FTM_config_struct.interruptEnable);
	FTM_BDMmode(FTM_config_struct.FTM, FTM_config_struct.BDMselector);
}

void FTM_channelConfig(FTM_channel_config_t FTM_channel_struct){
	FTM_channelStatusAndControl(FTM_channel_struct.FTM, FTM_channel_struct.FTMchannel, FTM_channel_struct.CSCselector);
	FTM_setChannelValue(FTM_channel_struct.FTM, FTM_channel_struct.FTMchannel, FTM_channel_struct.FTMchannelValue);
	FTM_enableChannelInterrupt(FTM_channel_struct.FTM, FTM_channel_struct.FTMchannel, FTM_channel_struct.channelInterruptEnable);
}

