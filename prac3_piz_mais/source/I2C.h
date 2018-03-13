/**
	\file
	\brief
		This is the header file for the I2C device driver.
		i.e., this is the application programming interface (API) for the GPIO peripheral.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo
	    Functions are not implemented.
 */

#ifndef I2C_H_
#define I2C_H_

#include "MK64F12.h"
#include "DataTypeDefinitions.h"
#include "GPIO.h"

/** Constant that represent the clock enable for GPIO A */
#define I2C0_CLOCK_GATING 0x40

#define I2CSLAVE_RTC 0xA2

#define I2CSLAVE_MEM 0xA0
/**
 * \brief This enum define the UART port to be used.
 */
typedef enum {SLAVE,MASTER}MasterOrSlaveType;
typedef enum {RECEIVE,TRANSMIT}ReceiveOrTransmitType;
typedef enum {I2C_0, I2C_1, I2C_2}I2C_ChannelType;

 /********************************************************************************************/
 /*!
  	 \brief
  	 	 Configures the I2C port based on the input parameters.
  	 	 Also, internally this function configures the GPIO, pin control register and clock gating, to be used as I2C.
  	 	 It is recommended to use pin 2 and 3 of GPIOB.
  	 \param[in] I2Cchannel It is the channel pointer to be used.
  	 \param[in] channel It is the channel to be used.
  	 \param[in] systemClock Frequency of the system.
  	 \param[in] baudRate baud rate between MCU and I2C device.
  	 \return void

  */
//void I2C_init(I2C_Type * I2Cchannel, I2C_ChannelType CGchannel, uint32 systemClock, uint8 baudRate);
void I2C0_init(uint32 systemClock, uint16 baudRate);

 /********************************************************************************************/
 /*!
  	 \brief
  	 	 Enables the I2C channel.
  	 \param[in] channel It is the channel to be enabled.
  	 \return void

  */
void I2C_enable(I2C_Type* I2Cchannel);

/********************************************************************************************/
/*!
 	 \brief
 	 	 Enables the I2C channel interrupt.
 	 \param[in] channel It is the channel interrupt to be enabled.
 	 \return void

 */
void I2C_interruptEnable(I2C_Type* I2Cchannel);

/********************************************************************************************/
/*!
 	 \brief
 	 	 Sets a baud rate value for the I2C channel.
 	 \param[in] channel It is the channel to be set.
 	 \param[in] baudRate baud rate between MCU and I2C device.
 	 \return void

 */
void I2C0_setBaudRate_100K(I2C_Type* I2Cchannel, uint32 systemClock, uint16 baudRate);

 /********************************************************************************************/
 /*!
  	 \brief
  	 	 Enables the I2C channel clock gating.
  	 \param[in] channel It is the channel to be opened.
  	 \return uint8 TRUE if configured correctly, FALSE if there was an error

  */
uint8 I2C_clockGating(I2C_ChannelType channel);

 /********************************************************************************************/
 /*!
  	 \brief
  	 	 Indicates the status of the bus regardless of slave or master mode. Internally checks the busy bit int the
  	 	 I2Cx_S register. This bit is set when a START signal is detected and cleared when a STOP signal is detected.
  	 \param[in] I2Cchannel Channel to check if busy.
  	 \return This function returns a 0 logic if the bus is idle and returns 1 logic if the bus is busy.

  */
// uint8 I2C_busy(I2C_Type* I2Cchannel);
void I2C_busy(I2C_Type* I2Cchannel);

 /********************************************************************************************/
 /*!
  	 \brief
  	 	 It selects between master or slave mode.
  	 \param[in] I2Cchannel Channel to set as master or slave.
  	 \param[in] masterOrSlave If == 1 master mode, if == 0 slave mode.
  	 \return void

  */
 void I2C_MSTOrSLVMode(I2C_Type* I2Cchannel, uint8 MasterOrSlave);
 /********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 It selects between transmitter mode or receiver mode.
  	 \param[in] I2Cchannel Channel to set.
  	 \param[in] txOrRx If == 1 transmitter mode, if == 0 receiver mode.
  	 \return void

  */
 void I2C_TXRXMode(I2C_Type* I2Cchannel, uint8 ReceiveOrTransmit);
 /********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 It generates the Not ACKnowledge that is needed when the master reads data.
  	 \return void

  */
 void I2C_NACK(I2C_Type* I2Cchannel);
 /********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 It generates a repeated start that is needed when master reads data.
  	 \return void

  */
 void I2C_repeatedStart(I2C_Type* I2Cchannel);
 /********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 It writes the data to be transmitted into the transmission buffer. When you want to
  	 	 write a value into the buffer you need to use this sentence I2C0_D = data. Avoid to use
  	 	 masks like this I2C0_D |= data.
  	 \param[in] I2Cchannel Channel to write.
  	 \return void

  */
void I2C_writeByte(I2C_Type* I2Cchannel, uint8 dataToWrite);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 It reads data from the receiving buffer.
 	 \param[in] I2Cchannel Channel to read.
 	 \return void

 */
uint8  I2C_readByte(I2C_Type* I2Cchannel);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 Indicates the status of the bus regardless of slave or master mode. Internally checks the busy bit int the
 	 	 I2Cx_S register. This bit is set when a START signal is detected and cleared when a STOP signal is detected.
 	 \param[in] I2Cchannel channel to hold on.
 	 \return This function returns a 0 logic if the bus is idle and returns 1 logic if the bus is busy.

 */
void I2C_wait(I2C_Type* I2Cchannel);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 Indicates if the acknowledge was received.
 	 \param[in] I2Cchannel channel to get its acknowledge.
 	 \return This function returns a 0 logic if the acknowledge was received and returns 1 logic if the acknowledge was not received.

 */
//uint8 I2C_getACK(I2C_Type* I2Cchannel);
void I2C_getACK(I2C_Type* I2Cchannel);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 Generates the start signal. When MST bit is changed from 0 to 1, a START signal is generated
 	 	 on the bus and master mode is selected. Also, inside the function the I2C is
 	 	 change to transmitter mode.
 	  \param[in] I2Cchannel channel to start.
 	 \return void

 */
void I2C_start(I2C_Type* I2Cchannel);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 Generates the stop signal. When this bit changes from 1 to 0, a STOP signal is generated
 	 	 and the mode of operation changes from master to slave. Also, inside the function the I2C is
 	 	 change to receiver mode.
 	  \param[in] I2Cchannel channel to stop.
 	 \return void

 */
void I2C_stop(I2C_Type* I2Cchannel);

#endif /* I2C_H_ */
