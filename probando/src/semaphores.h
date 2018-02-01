/*
 * semaphores.h
 *
 *  Created on: 08/09/2016
 *      Author: rperalez
 */

#ifndef SOURCE_SEMAPHORES_H_
#define SOURCE_SEMAPHORES_H_

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "stdio.h"

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"

/*#define USE_SEMAPHORE_CODE*/
/*#define USE_MUTEX_CODE*/

extern SemaphoreHandle_t xSemaphore;
extern void create_semaphore(void);
extern void create_mutex(void);
extern void semaphore_producer(void *pvParams);
extern void semaphore_consumer(void *pvParams);
extern void mutex_test(void *pvParams);

#endif /* SOURCE_SEMAPHORES_H_ */
