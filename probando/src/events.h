/*
 * events.h
 *
 *  Created on: 19/09/2016
 *      Author: Eunice Ibarra
 */

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "event_groups.h"
#include "timers.h"

#define USE_EVENTS_CODE

#define COUNT0  (1 << 0)
#define COUNT1  (1 << 1)
#define COUNT2  (1 << 2)
#define COUNT3  (1 << 3)
#define COUNT4  (1 << 4)
#define COUNT5  (1 << 5)
#define COUNT6  (1 << 6)
#define COUNT7  (1 << 7)
#define COUNT8  (1 << 8)
#define COUNT9  (1 << 9)

EventGroupHandle_t xEvents;

void events_monitor(void *pvParams);
