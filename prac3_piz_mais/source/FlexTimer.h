/*
 * FlexTimer.h
 *
 *	Brief: FlexTimer module driver
 *  Created on: 20/10/2017
 *      Author: Daniel Celis
 */

#ifndef FLEXTIMER_H_
#define FLEXTIMER_H_

#include "MK64F12.h"
#include "DataTypeDefinitions.h"

typedef enum{FTM_0,FTM_1,FTM_2,FTM_3}CG_FTM_selector_t;

typedef enum{MSA0,MSA1}MSAbit_t;
typedef enum{MSB0,MSB1}MSBbit_t;
typedef enum{ELSA0,ELSA1}ELSAbit_t;
typedef enum{ELSB0,ELSB1}ELSBbit_t;

typedef enum{CHANNEL0,CHANNEL1,CHANNEL2,CHANNEL3,CHANNEL4,CHANNEL5,CHANNEL6,CHANNEL7}FTMchannel_t;

typedef enum{OVERFLOW,PWM,INCAPTURE,OUTCOMPARE}FTMmode_t;
typedef enum{DISABLE,ENABLE}enableOrDisable_t;
typedef enum {BDM0,BDM1,BDM2,BDM3}BDMmode_t;
typedef enum{NOCLK,SYSCLK,FXCLK,EXCLK}clockSource_t;
typedef enum{DIV1,DIV2,DIV4,DIV8,DIV16,DIV32,DIV64,DIV128}prescalerFactor_t;

typedef uint16 channelValue;

typedef struct
{
	uint8 flagFTM0 : 1;
	uint8 flagFTM1 : 1;
	uint8 flagFTM2 : 1;
	uint8 flagFTM3 : 1;
} FTM_interruptFlags_t;

typedef struct
{
	uint8 flagCH0 : 1;
	uint8 flagCH1 : 1;
	uint8 flagCH2 : 1;
	uint8 flagCH3 : 1;
	uint8 flagCH4 : 1;
	uint8 flagCH5 : 1;
	uint8 flagCH6 : 1;
	uint8 flagCH7 : 1;
} FTM_channelInterruptFlags_t;

typedef struct{
	MSAbit_t MSA;
	MSBbit_t MSB;
	ELSAbit_t ELSA;
	ELSBbit_t ELSB;
}CSCbits_t;

typedef struct{
	CG_FTM_selector_t CG_FTM;
	FTM_Type * FTM;
	enableOrDisable_t FTM_writeProtectionEnable;
	uint16 moduloValue;
	clockSource_t clockSelector;
	prescalerFactor_t prescalerSelector;
	enableOrDisable_t interruptEnable;
	enableOrDisable_t registerWriteEnable;
	BDMmode_t BDMselector;
}FTM_init_config_t;

typedef struct{
	FTM_Type * FTM;
	uint8 FTMchannel;
	CSCbits_t CSCselector;
	enableOrDisable_t channelInterruptEnable;
	uint16 FTMchannelValue;
}FTM_channel_config_t;

/********************************************************************************************/
/*!
 	 \brief	 FTM0 interrupt handler.
 	 \return void
 */
void FTM0_IRQHandler(void);

uint32 GETiniVal(void);
uint32 GETfinVal(void);

/********************************************************************************************/
/*!
 	 \brief	 FTM clock gating enable.
 	 \param[in] FTM to enable.
 	 \return void
 */
void FTM_clockGating(CG_FTM_selector_t CG_FTM);

/********************************************************************************************/
/*!
 	 \brief	 FTM interrupt flag get.
 	 \param[in] FTM flag to return.
 	 \return Flag status
 */
uint8 FTM_getIRQStatus(CG_FTM_selector_t FTM);

/********************************************************************************************/
/*!
 	 \brief	 FTM0 channel interrupt flag get.
 	 \param[in] FTM0 channel flag to return.
 	 \return Flag status
 */
uint8 FTM0_getChannelIRQStatus(uint8 Channel);

/********************************************************************************************/
/*!
 	 \brief	 FTM interrupt flag clear.
 	 \param[in] FTM flag to clear.
 	 \return void
 */
uint8 FTM_clearIRQStatus(CG_FTM_selector_t FTM);

/********************************************************************************************/
/*!
 	 \brief	 FTM0 channel interrupt flag clear.
 	 \param[in] FTM0 channel flag to clear.
 	 \return void
 */
uint8 FTM0_clearChannelIRQStatus(uint8 Channel);

/********************************************************************************************/
/*!
 	 \brief	 FTM write protection enable. 0 protects the bits, 1 allows writing on the protected bits.
 	 \param[in] FTM to protect.
 	 \param[in] FTM_enabler write enable.
 	 \return void
 */
void FTM_writeProtectionEnable(FTM_Type * FTM, enableOrDisable_t FTM_writeProtectionEnable);

/********************************************************************************************/
/*!
 	 \brief	 FTM modulo value for the counter.
 	 \param[in] FTM to change its modulo value.
 	 \param[in] moduloValue value for the modulo register.
 	 \return void
 */
void FTM_modulo(FTM_Type * FTM, uint16 moduloValue);

/********************************************************************************************/
/*!
 	 \brief	 FTM clock source selection.
 	 \param[in] FTM to change its clock source.
 	 \param[in] clockSelector clock select for the FTM.
 	 \return void
 */
void FTM_clockSourceSelect(FTM_Type * FTM, clockSource_t clockSelector);

/********************************************************************************************/
/*!
 	 \brief	 FTM clock prescaler value selection.
 	 \param[in] FTM to change its prescaler factor.
 	 \param[in] prescalerSelector prescaler factor for the FTM.
 	 \return void
 */
void FTM_prescalerSelect(FTM_Type * FTM, prescalerFactor_t prescalerSelector);

/********************************************************************************************/
/*!
 	 \brief	 FTM interrupt enable.
 	 \param[in] FTM to enable its interrupts.
 	 \param[in] interruptEnable interrupt enable for the FTM.
 	 \return void
 */
void FTM_enableInterrupt(FTM_Type * FTM, enableOrDisable_t interruptEnable);

/********************************************************************************************/
/*!
 	 \brief	 FTM channel-specific interrupt enable.
 	 \param[in] FTM where the channel is located.
 	 \param[in] Channel to enable its interrupts.
 	 \param[in] interruptEnable interrupt enable for the FTM channel.
 	 \return void
 */
void FTM_enableChannelInterrupt(FTM_Type * FTM, uint8 FTMchannel, enableOrDisable_t channelInterruptEnable);

/********************************************************************************************/
/*!
 	 \brief	 FTM register write enable.
 	 \param[in] FTM to enable writing.
 	 \param[in] writeEnable register write enable for the FTM.
 	 \return void
 */
void FTM_enableRegisterWrite(FTM_Type * FTM, enableOrDisable_t registerWriteEnable);

/********************************************************************************************/
/*!
 	 \brief	 FTM channel status and control through a 4-bit structure to a channel.
 	 \param[in] FTM to configure.
 	 \param[in] FTM channel to configure.
 	 \param[in] CSCselector structure for MSA, MSB, ELSA and ELSB bits.
 	 \return void
 */
void FTM_channelStatusAndControl(FTM_Type * FTM, uint8 FTMchannel, CSCbits_t CSCselector);

/********************************************************************************************/
/*!
 	 \brief	 Assignment of a value to a channel.
 	 \param[in] FTM to configure.
 	 \param[in] FTM channel to configure.
 	 \param[in] FTMchannelValue value for CnV.
 	 \return void
 */
uint16 FTM_getChannelValue(FTM_Type * FTM, uint8 FTMchannel);

/********************************************************************************************/
/*!
 	 \brief	 Assignment of a value to a channel.
 	 \param[in] FTM to configure.
 	 \param[in] FTM channel to configure.
 	 \param[in] FTMchannelValue value for CnV.
 	 \return void
 */
void FTM_setChannelValue(FTM_Type * FTM, uint8 FTMchannel, uint16 FTMchannelValue);

/********************************************************************************************/
/*!
 	 \brief	 Clear the timer overflow flag.
 	 \param[in] FTM to clear.
 	 \return void
 */
void FTM_clearOverflowFlag(FTM_Type * FTM);

/********************************************************************************************/
/*!
 	 \brief	 Clear the FTM channel flag.
 	 \param[in] FTM where the channel is.
 	 \param[in] Channel to clear.
 	 \return void
 */
void FTM_clearChannelFlag(FTM_Type * FTM, uint8 FTMchannel);

/********************************************************************************************/
/*!
 	 \brief	Select BDM mode for the FTM.
 	 \param[in] FTM to clear.
 	 \param[in] BDM selector.
 	 \return void
 */
void FTM_BDMmode(FTM_Type * FTM, BDMmode_t BDMselector);

/********************************************************************************************/
/*!
 	 \brief	Initialization sequence according to the set configuration structure.
 	 \param[in] FTM_init_config_t configuration structure.
 	 \return void
 */
void FTM_init(FTM_init_config_t FTM_config_struct);

/********************************************************************************************/
/*!
 	 \brief	Channel configuration.
 	 \param[in] FTM_channel_config_t for the channel configuration parameter structure.
 	 \return void
 */
void FTM_channelConfig(FTM_channel_config_t FTM_channel_struct);

#endif /* FLEXTIMER_H_ */
