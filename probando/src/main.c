/*
 * Copyright (c) 2013 - 2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * This is template for main module created by New Kinetis SDK 2.x Project Wizard. Enjoy!
 **/

#include <string.h>

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
/*#include "fsl_debug_console.h"*/
#include "fsl_port.h"
#include "queues.h"
#include "semaphores.h"
#include "events.h"

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"


/* Task priorities . */
#define red_task_PRIORITY       ( configMAX_PRIORITIES - 1 )
#define blue_task_PRIORITY      ( red_task_PRIORITY - 1 )
#define queue_rx_PRIORITY       ( configMAX_PRIORITIES - 1 )
#define queue_tx_PRIORITY       (queue_rx_PRIORITY - 1)
#define sem_producer_PRIORITY   (configMAX_PRIORITIES - 1 )
#define sem_consumer_PRIORITY   (sem_producer_PRIORITY - 1 )
#define mutex_task_PRIORITY     (configMAX_PRIORITIES - 1 )
#define event_task_PRIORITY     (configMAX_PRIORITIES - 1)

/*!
 * @brief Application entry point.
 */
int main(void) {
    /* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Add your code here */
    // Enable clock for LED' s ports
    CLOCK_EnableClock(kCLOCK_PortB);
    CLOCK_EnableClock(kCLOCK_PortE);

    // Set pin as GPIO
    PORT_SetPinMux(BOARD_LED_RED_GPIO_PORT, BOARD_LED_RED_GPIO_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(BOARD_LED_BLUE_GPIO_PORT, BOARD_LED_BLUE_GPIO_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(BOARD_LED_GREEN_GPIO_PORT, BOARD_LED_GREEN_GPIO_PIN, kPORT_MuxAsGpio);

    // Initialize red and green leds
    LED_RED_INIT(LOGIC_LED_OFF);
    LED_BLUE_INIT(LOGIC_LED_OFF);
    LED_GREEN_INIT(LOGIC_LED_OFF);

    create_mutex();
    create_semaphore();
#ifdef USE_EVENTS_CODE
    /* Create event group */
    xEvents = xEventGroupCreate();
#endif

    /* Create RTOS task */
    xTaskCreate(semaphore_consumer, "sem_consumer", 2 * configMINIMAL_STACK_SIZE,
                NULL, sem_consumer_PRIORITY, NULL);
    xTaskCreate(semaphore_producer, "sem_producer", 2 * configMINIMAL_STACK_SIZE,
                NULL, sem_producer_PRIORITY, NULL);
    xTaskCreate(mutex_test, "mutex_test", 2 * configMINIMAL_STACK_SIZE,
                    NULL, mutex_task_PRIORITY, NULL);
    xTaskCreate(queue_sender, "queue_tx", 2 * configMINIMAL_STACK_SIZE, NULL,
                    queue_tx_PRIORITY, NULL);
    xTaskCreate(queue_receiver, "queue_rx", 2 * configMINIMAL_STACK_SIZE, NULL,
                    queue_rx_PRIORITY, NULL);
#ifdef USE_EVENTS_CODE
    xTaskCreate(events_monitor, "events_monitor", 2 * configMINIMAL_STACK_SIZE, NULL,
                event_task_PRIORITY, NULL);
#endif
    vTaskStartScheduler();

    for(;;) { /* Infinite loop to avoid leaving the main function */
        __asm("NOP"); /* something to use as a breakpoint stop while looping */
    }
}



