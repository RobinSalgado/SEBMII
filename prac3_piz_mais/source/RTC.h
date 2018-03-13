#ifndef RTC_H_
#define RTC_H_

#include "I2C.h"
#include "DataTypeDefinitions.h"
#include "LCDNokia5110.h"

#define _24_HOURS 0
#define _12_HOURS 1

#define AM 	0
#define PM  1

//uint16 leapYear = 0;

typedef enum {
	WRITE, READ
} I2C_RW_t;

extern void delay(uint16);

typedef enum {
	CONTROL_STATUS,
	HUNDREDS,
	SECONDS,
	MINUTES,
	HOURS,
	YEAR_DATE,
	WEEKDAYS_MONTH,
	TIMER,
	ALARM_CONTROL
} RTC_registers_t;

typedef enum {
	MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY
} Weekdays_t;

//String structure for the BCD temperature format
typedef struct {
	uint8 units : 4;
	uint8 tens : 4;
	uint8 hundreds : 4;
	uint8 thousands : 4;
} BCD_struct;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!							Register Struct types											*/

/*!Memory location 00h*/
typedef struct {
	/*!Seconds flag if alarm enable bit*/
	uint8 timer_flag :1; // logic 0
	/*!Minutes if alarm enable bit*/
	uint8 alarm_flag :1; // logic 0
	/*!0: Alarm disabled: register 08h can be used as free ram
	 * 1: Alarm enabled: register 08h  is the alarm control register*/
	uint8 alarm_enable_bit :1;
	/*! logic 0: read locations 05h to 06h unmasked
	 logic 1: read date and month count directly*/
	uint8 mask_flag :1;
	/*!Function mode
	 * 00: clock mode 32.768 kHz
	 * 01: clock mode 50 Hz
	 * 10: event-counter mode
	 * 11: test modes*/
	uint8 function_mode :2;
	/*! logic 0: count
	 logic 1: store and hold last count in, capture latches*/
	uint8 last_count_flag :1;
	/*! logic 0: count pulses
	 logic 1: stop counting, reset divider*/
	uint8 stop_count_flag :1;

} RTC_ControlAndStatus_t;
/*!Memory location 01h (hundreds counter)*/
typedef struct {
	uint8 Hundreds :4; // BCD
	uint8 decimals :4;

/*!Memory location 02h (seconds counter)*/
} RTC_HundredsSeconds_t;

typedef struct {
	uint8 secondsUnits :4; // BCD
	uint8 secondsTens :4;
} RTC_Seconds_t;

/*!Memory location 03h (minutes counter)*/
typedef struct {
	uint8 minutesUnits :4; // BCD
	uint8 minutesTens :4;
} RTC_Minutes_t;

/*!Memory location 04h (hours counter)*/
typedef struct {
	uint8 hours_units :4; // BCD
	uint8 hours_tens :2; //binary
	/*!0: AM
	 * 1: PM*/
	uint8 AMorPM_flag :1;
	/*!0: 24 hr format, AM/PM flag remains unchanged
	 1: 12 hr format, AM/PM flag will be updated */
	uint8 format :1;

} RTC_HoursCounter_t;

/*!Memory location 05h (hours counter)*/
typedef struct {
	uint8 days_units :4; // BCD
	uint8 days_tens :2; //Binary

	/*!year (0 to 3 binary, read as logic 0 if the mask flag is set)*/
	uint8 year :2;

} RTC_YearAndDate_t;

/*!Memory location 06h (weekdays/months)*/
typedef struct {
	uint8 months_units :4; // BCD
	uint8 months_tens :1;
	/*!weekdays (0 to 6 binary, read as logic 0 if the mask flag is set)*/
	uint8 weekday :3;
} RTC_MonthsAndWeekday_t;

typedef union {
	uint8 data;
	RTC_HundredsSeconds_t hundreds;
	RTC_Seconds_t seconds;
	RTC_Minutes_t minutes;
	RTC_HoursCounter_t hours;
	RTC_MonthsAndWeekday_t monthsAndWeekday;
	RTC_YearAndDate_t yearAndDate;
	BCD_struct yearBCD;
} RTC_timeUnion_t;

typedef struct {
	RTC_timeUnion_t hundreds;
	RTC_timeUnion_t seconds;
	RTC_timeUnion_t minutes;
	RTC_timeUnion_t hours;
	RTC_timeUnion_t monthsAndWeekday;
	RTC_timeUnion_t yearAndDate;
	RTC_timeUnion_t yearBCD;
} RTC_timeStruct_t;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/

/*! Initialization
 When power-on occurs the I2C-bus interface, the control and status register and all clock
 counters are reset.
 The device starts time-keeping in the 32.768 kHz clock mode with the
 24 hour format on the first of January at 0.00.00:00.
 A 1 Hz square wave with 50 % duty

 cycle appears at the interrupt output pin (starts HIGH).

 IMPORTANT: The stop counting flag of the control and status register must be set before loading the
 actual time into the counters. Loading of illegal states leads to a temporary clock
 malfunction.*/

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief RTC initialization

 \param[in] I2C channel
 \return void
 */

void RTC_init(void);

/*!
 \brief RTC start condition is given as a HIGH to LOW transition in the SDL as the SCL
 is HIGH.

 \param[in] I2C channel
 \return void
 */

void RTC_start(void);

/*!
 \brief RTC stop condition is given as a LOW to HIGH transition in the SDL as the SCL
 is HIGH.

 \param[in] I2C channel
 \return void
 */

void RTC_stop(void);

/*!
 \brief A slave receiver must generate an acknowledge after the reception of each byte.
 • Also a master receiver must generate an acknowledge after the reception of each
 byte that has been clocked out of the slave transmitter.
 • The device that acknowledges must pull-down the SDA line during the acknowledge
 clock pulse, so that the SDA line is stable LOW during the HIGH period of the
 acknowledge related clock pulse (set-up and hold times must be taken into
 consideration).
 • A master receiver must signal an end of data to the transmitter by not generating an
 acknowledge on the last byte that has been clocked out of the slave. In this event, the
 transmitter must leave the data line HIGH to enable the master to generate a STOP
 condition.

 \param[in] I2C channel
 \return uint8 ack
 */

uint8 RTC_acknowledge(void);

/*!
 \brief Time can be set by writing into the first registers

 \param[in] address
 \param[in] I2C channel
 \return void
 */

void RTC_singleWrite(uint8 BUSaddress, RTC_registers_t timeRegister,
		uint8 dataToWrite);

/*!
 \brief The Master to slave write mode is defined by writing 2 byte to the I2C bus
 and a n-byte data set.
 * Slave address
 * Register address
 * Data to read


 \param[in] Slave
 \param[in] Register
 \param[in] Data
 \return void
 */

uint8 RTC_singleRead(uint8 BUSaddress, RTC_registers_t timeRegister);

/*!
 \brief The Master to slave read mode is defined by writing 2 byte to the I2C bus
 and a n-byte reception
 * Slave address
 * Register address
 * Data to read


 \param[in] Slave
 \param[in] Register
 \param[in] Data
 \return void
 */

RTC_timeStruct_t RTC_timeRead(uint8 BUSaddress);

/*!
 \brief The Master to slave read mode is defined by writing 2 byte to the I2C bus
 and a n-byte reception
 * Slave address
 * Register address
 * Data to read


 \param[in] Slave
 \param[in] Register
 \param[in] Data
 \return void
 */

void RTC_setTime(uint8 BUSaddress, RTC_timeStruct_t * time);

void RTC_printTime(RTC_timeStruct_t time);

uint8 setYear(uint16 year, RTC_timeStruct_t * time);

BCD_struct yearToBCD(RTC_timeStruct_t * time);

uint16 getLeapYear();

void setLeapYear(uint16 year);

RTC_timeStruct_t * getTime();



#endif /* RTC_H_ */
