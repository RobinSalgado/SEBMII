/*
 * events.c
 *
 *  Created on: 19/09/2016
 *      Author: Eunice Ibarra
 */

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "stdio.h"
#include "queues.h"

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "events.h"
#include "timers.h"

EventGroupHandle_t xEvents;

void events_monitor(void *pvParams)
{
	EventBits_t bits;
    for (;;)
    {
#ifdef USE_EVENTS_CODE
    	bits = xEventGroupWaitBits(xEvents, (COUNT0 | COUNT1 | COUNT2 | COUNT3 | COUNT4 |
    								COUNT5 | COUNT6 | COUNT7 | COUNT8 | COUNT9), pdTRUE,
    								pdTRUE,portMAX_DELAY);

    	/* Count from 0 to 9 is completed causing the green LED to toggle */
    	LED_GREEN_TOGGLE();
#endif
    	vTaskDelay(10);
    }
}
