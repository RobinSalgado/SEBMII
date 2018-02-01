/*
 * semaphores.c
 *
 *  Created on: 08/09/2016
 *      Author: rperalez
 */

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "stdio.h"
#include "semaphores.h"

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"

/* Step 1 – Declare the handler */
SemaphoreHandle_t xSemaphore;
SemaphoreHandle_t xMutex;

void create_semaphore(void)
{
#ifdef USE_SEMAPHORE_CODE
    /* Chose the type of semaphore to be created */
    xSemaphore = xSemaphoreCreateBinary();
    /* xSemaphore = xSemaphoreCreateBinaryStatic(
                        StaticSemaphore_t *pxSemaphoreBuffer ); */
    /*xSemaphore = xSemaphoreCreateCounting( 5, 0 );*/
    /* xSemaphore = xSemaphoreCreateCountingStatic( 10, 0, &xSemaphoreBuffer );*/
#endif
}

void create_mutex(void)
{
#ifdef USE_MUTEX_CODE
    /* Or you can create a mutex with a semaphore handler */
    xMutex = xSemaphoreCreateMutex();
    /*xMutex = xSemaphoreCreateMutexStatic(StaticSemaphore_t *pxMutexBuffer );*/
#endif
}

void semaphore_producer(void *pvParams)
{
    for (;;)
    {
#ifdef USE_SEMAPHORE_CODE
        /* when there's a new semaphore to be posted we use*/
        xSemaphoreGive( xSemaphore );

        LED_BLUE_TOGGLE();
#endif

        vTaskDelay(2000);
    }
}

void semaphore_consumer(void *pvParams)
{
    for (;;)
    {
#ifdef USE_SEMAPHORE_CODE
        /* When we need to wait for a semaphore we use */
        if (pdTRUE != xSemaphoreTake( xSemaphore, ( TickType_t ) 100))
        {
            LED_RED_TOGGLE();
        }
#endif

        vTaskDelay(1000);
    }

}

void mutex_test(void *pvParams)
{
    for (;;)
    {
#ifdef USE_MUTEX_CODE
        /* in the case of mutex, we use the same take and give APIs but there are
         * additional restrictions covered through the slides*/
        /* xSemaphoreTake( xMutex, ( TickType_t ) timeout ) */

        /* xSemaphoreGive( xMutex ); */
#endif
        vTaskDelay(1000);
    }
}



