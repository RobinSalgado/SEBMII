#include "alarm.h"

/* 							**CORRECTING STANDARD ERRORS**
 * 1.1 should be "int32_t" instead of only "integer"ensures that no future port
 *     of the code will encounter an unexpected overflow
 *
 * 1.2 placement  of constants on the left side of an equivalence (==) test
 *
 * 1.3 The length of all lines in a program shall be limited to a maximum of 80
 *     characters.
 *
 * 1.4 Each left brace ('{') shall appear by itself on the line below the start
 *     of the block it opens The corresponding right brace ('}') shall appear
 *     by itself in the same position the appropriate number of lines later in
 *     the file.
 *
 * 1.5 Unless it is a single identifier or constant, each operand of the logical
 *     && and || operators shall be surrounded by parentheses.
 *
 * 1.6 keywords to avoid  "continue", "break", "goto" they shall not be used
 *
 * 1.7 The names of all new data types, including structures, unions, and
 *     enumerations, shall consist only of lowercase characters and internal
 *     undersocres and end with '_t
 *
 * 1.8 It is preferable to create variables as you need them, rather than
 *     all at the top of a function. Example:
 *     for (int loop = 0; loop < MAX_LOOPS; loop++)
 *     {
 *         ...
 *     }
 *
 * 1.9  Nested if-else statements shall not be deeper than two levels. Use
 *      functions calls or switch statements to reduce complexity and aid
 *      understanding.
 *
 * 2.0 Don't use magic numbers in loops
 * */

typedef struct
{

	int seconds;	// error 1.1 & 1.7
	int minutes;	// error 1.1 & 1.7
	int hours;		// error 1.1 & 1.7
	int enabled;	// error 1.1 & 1.7
}time;

time current_hour;
time alarm[13];
int alarm_number = 0; // error 1.1 & 1.7

int set_alarm(int seconds, int minutes, int hours, int enabled)// error 1.1 & 1.7
{
	int retval = 0; // error 1.1
	if(alarm_number < 13)
	{
		alarm[alarm_number].seconds = seconds;
		alarm[alarm_number].minutes = minutes;
		alarm[alarm_number].hours = hours;
		alarm[alarm_number].enabled = enabled;
		alarm_number++;
		retval = 1;
	}
	return retval;
	
}

int check_status(void)
{
	int retval; // error 1.1 & 1.7
	int i; // error 1.1 & 1.7
	for(i = 0 ; i < 13 ; i++) // error 1.8 & 2.0
	{
		if(alarm[i].enabled)
		{
			continue; // error 1.6
		}
											// error 1.3 & 1.5
		if(current_hour.seconds == alarm[i].seconds && current_hour.minutes == alarm[i].minutes && current_hour.hours == alarm[i].hours)
		{
			retval = 1;
			break; // error 1.6
		}
	}
	retval = 0;
	return retval;
}

//This function should be called in an interruption every 1 second
void refresh_hour(void)
{
	if(current_hour.seconds==59){ // error 1.2 & 1.4
		current_hour.seconds = 0;
		if(current_hour.minutes == 59){ //error 1.2 & 1.4
		current_hour.minutes = 0;	
	if(current_hour.hours == 23)//error 1.2
	{
		current_hour.hours = 0;
	}else{ //error 1.4
	current_hour.hours++;
	}
		}else{ //error 1.4
			current_hour.minutes++;		
		}
		
	} // error 1.4
	else{ // error 1.4 & 1.9
		current_hour.seconds++;	
	}//error 1.4
}
