/*
 * UART_RTC_sequences.c
 *
 *  Created on: 09/11/2017
 *      Author: Oscar
 *       */
#include "UART_RTC_sequences.h"

extern UART_MailBoxType UART0_MailBox;

uint8 UART_RTCaddressRetrieval(void) {
	uint8 addressPosition = 0;	//Auxiliary variable to move through the array
	uint8 addressArray[3] = { };	//Auxiliary array to save the retrieved data
	uint8 address = 0;		//Auxiliary variable to store the calculated address

	UART0_MailBox.mailBox = FALSE;//Clear the mailbox to avoid the previous enter
	UART0_MailBox.flag = FALSE;	//Clear the flag to appropriately retrieve new data

	while (UART0_MailBox.mailBox != 13) {	//Wait until an enter is received
		UART_PITsequence();
		if (UART0_MailBox.flag) {		//If a new data arrives to the mailbox
			//moved flag from bottom to top
			UART0_MailBox.flag = FALSE;		//clear the reception flag
			addressArray[addressPosition] = UART0_MailBox.mailBox;//retrieve the data and save on the array
			UART_putChar(UART0, addressArray[addressPosition]);	//Echo to the UART
			addressPosition++;			//Move the array pointer
		}
	}
	UART0_MailBox.mailBox = FALSE;//After the enter is received, clear the mailbox
	UART0_MailBox.flag = FALSE;

	if (addressArray[0] >= 65)
		address = (addressArray[0] - '7') * 16;	//Multiply by 16^1
	else
		address = (addressArray[0] - '0') * 16;
	if (addressArray[1] >= 65)
		address += addressArray[1] - '7';			//Multiply by 16^0
	else
		address += addressArray[1] - '0';

	return (address);	//Return the calculated address
}

uint8 UART_RTClengthRetrieval(void) {
	uint8 lengthPosition = 0;	//Auxiliary variable to move through the array
	uint8 lengthArray[3] = { };	//Auxiliary array to save the retrieved data
	uint8 length;			//Auxiliary variable to store the calculated length

	UART0_MailBox.mailBox = FALSE;//Clear the mailbox to avoid the previous enter
	UART0_MailBox.flag = FALSE;	//Clear the flag to appropriately retrieve new data

	while (UART0_MailBox.mailBox != 13) {	//Wait until an enter is received
		UART_PITsequence();
		if (UART0_MailBox.flag) {		//If a new data arrives to the mailbox
			//moved flag from bottom to top
			UART0_MailBox.flag = FALSE;			//clear the reception flag
			lengthArray[lengthPosition] = UART0_MailBox.mailBox;//retrieve the data and save on the array
			UART_putChar(UART0, lengthArray[lengthPosition]);//Echo to the UART
			lengthPosition++;	//Move the array pointer
		}
	}
	UART0_MailBox.mailBox = FALSE;//After the enter is received, clear the mailbox
	UART0_MailBox.flag = FALSE;

	length = (lengthArray[0] - '0') * 10;	//First length data by 10
	length += lengthArray[1] - '0';			//Second as units

	return (length);		//Return length
}

void UART_RTCdataStorage(uint8 address) {
	uint8 dataPosition = 0;		//Auxiliary variable to move through the array
	uint8 saveAux;					//Auxiliary variable for the save sequence
	uint8 saveAddress = address;	//Temporary address to move it
	uint8 dataArray[64] = { };		//Auxiliary array to save the retrieved data

	UART0_MailBox.mailBox = FALSE;//Clear the mailbox to avoid the previous enter
	UART0_MailBox.flag = FALSE;	//Clear the flag to appropriately retrieve new data

	while (UART0_MailBox.mailBox != 13) {	//Wait until an enter is received
		UART_PITsequence();
		if (UART0_MailBox.flag) {		//If a new data arrives to the mailbox
			//moved flag from bottom to top
			UART0_MailBox.flag = FALSE;		//clear the reception flag
			dataArray[dataPosition] = UART0_MailBox.mailBox;//retrieve the data and save on the array
			UART_putChar(UART0, dataArray[dataPosition]);	//Echo to the UART
			dataPosition++;		//Move the array pointer
		}
	}
	UART0_MailBox.mailBox = FALSE;//After the enter is received, clear the mailbox
	UART0_MailBox.flag = FALSE;

	for (saveAux = 0; saveAux <= dataPosition; saveAux++) {	//Sequence to input the array onto the memory
		RTC_singleWrite(I2CSLAVE_RTC, saveAddress, dataArray[saveAux]);	//Call save function
		saveAddress++;	//Move address
	}

}

void UART_RTC_readHourSequence() {
	uint8 flag;
	while (UART0_MailBox.mailBox != 27) {
		flag = UART_PITsequence();
		//Wait for <esc> to return to main menu after a sequence.
		if (flag) {
			UARTMenu_readHour();
		}
	}
	UART0_MailBox.flag = FALSE;
	UART0_MailBox.mailBox = FALSE;
}

void UART_RTC_readDateSequence() {
	uint8 flag;
	while (UART0_MailBox.mailBox != 27) {
		flag = UART_PITsequence();
		//Wait for <esc> to return to main menu after a sequence.
		if (flag) {
			UARTMenu_readDate();
		}
	}
	UART0_MailBox.flag = FALSE;
	UART0_MailBox.mailBox = FALSE;
}

void UART_RTC_hourStorage(){
	uint16 hourPosition = 0;		//Auxiliary variable to move through the array
	uint8 hourArray[8] = {};		//Auxiliary array to save the retrieved hour
	uint8 dotFlag = 1;

	UART0_MailBox.mailBox = FALSE;	//Clear the mailbox to avoid the previous enter
	UART0_MailBox.flag = FALSE;		//Clear the flag to appropriately retrieve new data

	while(UART0_MailBox.mailBox != 13){		//Wait until an enter is received
		UART_PITsequence();
		if (UART0_MailBox.flag) {			//If a new data arrives to the mailbox
			//moved flag from bottom to top
			UART0_MailBox.flag = FALSE;		//clear the reception flag
			hourArray[hourPosition] = UART0_MailBox.mailBox;	//retrieve the data and save on the array
			UART_putChar(UART0,hourArray[hourPosition]);		//Echo to the UART
			if(dotFlag == 2){				//Set hour dots every two received bytes
				UART_putChar(UART0,':');
				dotFlag = FALSE;
			}
			dotFlag++;
			hourPosition++;		//Move the array pointer
		}
	}
	UART0_MailBox.mailBox = FALSE;	//After the enter is received, clear the mailbox
	UART0_MailBox.flag = FALSE;

	RTC_HoursCounter_t hourAux;		//auxiliary variables
	RTC_Minutes_t minuteAux;
	RTC_Seconds_t secondAux;

	//Convert from the BCD format retrieved from the UART to the RTC structures
	hourAux.hours_tens = hourArray[0] - '0';
	hourAux.hours_units = hourArray[1] - '0';
	minuteAux.minutesTens = hourArray[2] -'0';
	minuteAux.minutesUnits = hourArray[3] - '0';
	secondAux.secondsTens = hourArray[4] - '0';
	secondAux.secondsUnits = hourArray[5] - '0';

	//Get the current time values
	//Set the new values on the corresponding registers
	RTC_timeStruct_t * timeToSet = getTime();
	timeToSet->hours.hours.format = _24_HOURS;
	timeToSet->hours.hours.hours_tens = hourAux.hours_tens;
	timeToSet->hours.hours.hours_units = hourAux.hours_units;
	timeToSet->minutes.minutes = minuteAux;
	timeToSet->seconds.seconds = secondAux;

	RTC_setTime(I2CSLAVE_RTC, timeToSet);
}

void UART_RTC_dateStorage(){
	uint16 datePosition = 0;		//Auxiliary variable to move through the array
	uint8 dateArray[10] = {};		//Auxiliary array to save the retrieved hour

	UART0_MailBox.mailBox = FALSE;	//Clear the mailbox to avoid the previous enter
	UART0_MailBox.flag = FALSE;		//Clear the flag to appropriately retrieve new data

	while(UART0_MailBox.mailBox != 13){		//Wait until an enter is received
		UART_PITsequence();
		if (UART0_MailBox.flag) {			//If a new data arrives to the mailbox
			//moved flag from bottom to top
			UART0_MailBox.flag = FALSE;		//clear the reception flag
			dateArray[datePosition] = UART0_MailBox.mailBox;	//retrieve the data and save on the array
			UART_putChar(UART0,dateArray[datePosition]);		//Echo to the UART
			datePosition++;		//Move the array pointer
		}
	}
	UART0_MailBox.mailBox = FALSE;	//After the enter is received, clear the mailbox
	UART0_MailBox.flag = FALSE;

	RTC_YearAndDate_t yearAux;
	RTC_MonthsAndWeekday_t monthAux;

	monthAux.months_tens = dateArray[0] - '0';
	monthAux.months_units = dateArray[1] - '0';
	yearAux.days_tens = dateArray[2] - '0';
	yearAux.days_units = dateArray[3] - '0';

	uint16 auxYear;
	auxYear = (dateArray[4] - '0') * 1000;
	auxYear += (dateArray[5] - '0') * 100;
	auxYear += (dateArray[6] - '0') * 10;
	auxYear += (dateArray[7] - '0');

	RTC_timeStruct_t * timeToSet = getTime();
	timeToSet->monthsAndWeekday.monthsAndWeekday = monthAux;
	timeToSet->yearAndDate.yearAndDate = yearAux;
	RTC_setTime(I2CSLAVE_RTC, timeToSet);
	setYear(auxYear,timeToSet);
}

void UART_RTC_setWeekdaySequence(){
	uint8 weekdayAux = 0;

	while(UART0_MailBox.mailBox != 13){		//Wait until an enter is received
			UART_PITsequence();
			if (UART0_MailBox.flag) {			//If a new data arrives to the mailbox
				//moved flag from bottom to top
				UART0_MailBox.flag = FALSE;		//clear the reception flag
				weekdayAux = UART0_MailBox.mailBox;	//retrieve the data and save on the array
				UART_putChar(UART0,weekdayAux);		//Echo to the UART
			}
		}
	UART0_MailBox.mailBox = FALSE;	//After the enter is received, clear the mailbox
	UART0_MailBox.flag = FALSE;
	RTC_timeStruct_t * timeToSet = getTime();
	timeToSet->monthsAndWeekday.monthsAndWeekday.weekday = weekdayAux - '1';
	RTC_setTime(I2CSLAVE_RTC, timeToSet);
}

void UART_RTC_setHourSequence(){
	UART_putString(UART0, "\033[10;10H");	//<10,10> position on Tera Term
	UART_putString(UART0, "Write new hour (24H format)(HH:MM:SS): ");	//User interface string
	UART_RTC_hourStorage();	//Wait for <data><enter>
	UART_putString(UART0, "\033[11;10H");		//<10,11> position on Tera Term
	UART_putString(UART0, "Hour set successfully");	//User interface string
}

void UART_RTC_setDateSequence(){
	UART_putString(UART0, "\033[10;10H");	//<10,10> position on Tera Term
	UART_putString(UART0, "Write new date(MMDDYYYY): ");	//User interface string
	UART_RTC_dateStorage();	//Wait for <data><enter>
	UART_putString(UART0, "\033[11;10H");		//<10,11> position on Tera Term
//	UART_putString(UART0, "Write weekday (1 = Monday - 7 = Sunday): ");	//User interface string
//	UART_RTC_setWeekdaySequence();
//	UART_putString(UART0, "\033[12;10H");		//<10,12> position on Tera Term
	UART_putString(UART0, "Date set successfully");	//User interface string
}

uint8 UART_PITsequence() {
	uint8 PITflag = FALSE;
	RTC_timeStruct_t * auxTime;
	auxTime = getTime();

	if (FALSE != PIT_getIRQStatus(PIT_0)) {
		PIT_clearIRQStatus(PIT_0);
		(*auxTime) = RTC_timeRead(I2CSLAVE_RTC);
		RTC_printTime(*auxTime);
		PITflag = TRUE;
	}
	return PITflag;
}

void UARTMenu_readHour() {
	uint8 readAux;//Auxiliary variable to move through the array for the retrieval sequence
	uint8 readAddress = 0x00;		//Temporary address to move it
	RTC_timeUnion_t dataArray[WEEKDAYS_MONTH + 1] = { };	//Auxiliary array to save the retrieved data

	for (readAux = 0; readAux < (WEEKDAYS_MONTH + 1); readAux++) {	//Retrieval sequence
		dataArray[readAux].data = RTC_singleRead(I2CSLAVE_RTC, readAddress);//Get data from memory
		readAddress++;		//Move address
	}

	/*!Print hour with hh:mm:ss format*/
	UART_putString(UART0, "\033[2J");
	UART_putString(UART0, "\033[10;10H");
	UART_putChar(UART0, dataArray[HOURS].hours.hours_tens + '0');//Send array to the UART
	UART_putChar(UART0, dataArray[HOURS].hours.hours_units + '0');//Send array to the UART
	UART_putChar(UART0, ':');
	UART_putChar(UART0, dataArray[MINUTES].minutes.minutesTens + '0');//Send array to the UART
	UART_putChar(UART0, dataArray[MINUTES].minutes.minutesUnits + '0');	//Send array to the UART
	UART_putChar(UART0, ':');
	UART_putChar(UART0, dataArray[SECONDS].seconds.secondsTens + '0');//Send array to the UART
	UART_putChar(UART0, dataArray[SECONDS].seconds.secondsUnits + '0');	//Send array to the UART

	/*!Print AM/PM if flag is valid*/
	if (_12_HOURS == dataArray[HOURS].hours.format) {
		if (AM == dataArray[HOURS].hours.AMorPM_flag) {
			UART_putString(UART0, " AM");
		}else{
			UART_putString(UART0, " PM");
		}
	}

}

void UARTMenu_readDate(){
	uint8 readAux;//Auxiliary variable to move through the array for the retrieval sequence
	uint8 readAddress = 0x00;		//Temporary address to move it
	RTC_timeUnion_t dataArray[WEEKDAYS_MONTH + 1] = { };	//Auxiliary array to save the retrieved data
	BCD_struct year = yearToBCD(getTime());


	for (readAux = 0; readAux < (WEEKDAYS_MONTH + 1); readAux++) {	//Retrieval sequence
		dataArray[readAux].data = RTC_singleRead(I2CSLAVE_RTC, readAddress);//Get data from memory
		readAddress++;		//Move address
	}

	/*!Print hour with hh:mm:ss format*/
	UART_putString(UART0, "\033[2J");
	UART_putString(UART0, "\033[10;10H");
	UART_printWeekday(dataArray);
	UART_putChar(UART0, dataArray[WEEKDAYS_MONTH].monthsAndWeekday.months_tens + '0');//Send array to the UART
	UART_putChar(UART0, dataArray[WEEKDAYS_MONTH].monthsAndWeekday.months_units + '0');//Send array to the UART
	UART_putChar(UART0, '/');
	UART_putChar(UART0, dataArray[YEAR_DATE].yearAndDate.days_tens + '0');//Send array to the UART
	UART_putChar(UART0, dataArray[YEAR_DATE].yearAndDate.days_units + '0');	//Send array to the UART
	UART_putChar(UART0, '/');
	UART_putChar(UART0, year.thousands + '0');
	UART_putChar(UART0, year.hundreds + '0');
	UART_putChar(UART0, year.tens + '0');
	UART_putChar(UART0, year.units + '0');


}

void UART_printWeekday(RTC_timeUnion_t time[]) {
	switch (time[WEEKDAYS_MONTH].monthsAndWeekday.weekday) {
	case MONDAY:
		UART_putString(UART0, "Monday, ");
		break;
	case TUESDAY:
		UART_putString(UART0, "Tuesday, ");
		break;
	case WEDNESDAY:
		UART_putString(UART0, "Wednesday, ");
		break;
	case THURSDAY:
		UART_putString(UART0, "Thursday, ");
		break;
	case FRIDAY:
		UART_putString(UART0, "Friday, ");
		break;
	case SATURDAY:
		UART_putString(UART0, "Saturday, ");
		break;
	case SUNDAY:
		UART_putString(UART0, "Sunday, ");
		break;
	default:
		break;
	}
}

void UART_RTC_formatSequence() {
	uint8 mask = 0x80;				//Auxiliary variable for the save sequence
	uint8 dataRead;		//Auxiliary array to save the retrieved data
	uint8 decomposeAux;
	RTC_timeUnion_t dataAux;	//Auxiliary array to save the retrieved data

	dataAux.data = RTC_singleRead(I2CSLAVE_RTC, HOURS);	//Get data from memory

	/*!Print hour with hh:mm:ss format*/
	UART_putString(UART0, "\033[2J");
	UART_putString(UART0, "\033[10;10H");
	UART_putString(UART0, "Current format: ");

	/*!Print current format*/
	if (_12_HOURS == dataAux.hours.format) {
		UART_putString(UART0, " 12 Hours ");
	} else {
		UART_putString(UART0, " 24 Hours ");
	}

	UART_putString(UART0, "\033[12;10H");
	UART_putString(UART0, "Choose new format: ");
	UART_putString(UART0, "\033[13;14H");
	UART_putString(UART0, "[1] 12 hours ");
	UART_putString(UART0, "\033[14;14H");
	UART_putString(UART0, "[0] 24 hours ");

	UART0_MailBox.mailBox = FALSE;//Clear the mailbox to avoid the previous enter
	UART0_MailBox.flag = FALSE;	//Clear the flag to appropriately retrieve new data

	//Wait for a menu selection
	while (!UART0_MailBox.flag) {
		UART_PITsequence();
	}
	dataRead = UART0_MailBox.mailBox;
	UART0_MailBox.mailBox = FALSE;
	UART0_MailBox.flag = FALSE;
	dataRead -= '0';

	if (dataRead > 1) {

	} else {
		if (dataAux.data & mask) {
			if (_24_HOURS == dataRead) {
				decomposeAux = (dataAux.hours.hours_tens * 10)
						+ dataAux.hours.hours_units;
				if (12 == decomposeAux) {
					decomposeAux = 0;
				} else {
					decomposeAux = decomposeAux + 12;
				}
				dataAux.hours.hours_tens = (decomposeAux / 10) % 10;
				dataAux.hours.hours_units = (decomposeAux % 10);
				dataAux.data &= ~(mask);
				RTC_singleWrite(I2CSLAVE_RTC, HOURS, dataAux.data);
			}
		} else {
			if (_12_HOURS == dataRead) {
				decomposeAux = (dataAux.hours.hours_tens * 10)
						+ dataAux.hours.hours_units;
				if (0 == decomposeAux) {
					decomposeAux = 12;
				} else {
					decomposeAux = decomposeAux - 12;
				}
				dataAux.hours.hours_tens = (decomposeAux / 10) % 10;
				dataAux.hours.hours_units = (decomposeAux % 10);
				dataAux.data |= (mask);
				RTC_singleWrite(I2CSLAVE_RTC, HOURS, dataAux.data);

			}
		}

	}
}
