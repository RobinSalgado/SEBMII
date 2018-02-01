/*
 * queues.c
 *
 *  Created on: 04/09/2016
 *      Author: rperalez
 */
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "stdio.h"
#include "queues.h"

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "events.h"

TaskHandle_t queue_tx_task_handler;
TaskHandle_t queue_rx_task_handler;
/* step 1, declare the queue handler */
QueueHandle_t queue_handler;

char Message[] = {"Message 0"};

void queue_sender(void *pvParameters) {
    char local_count = '0';
    EventBits_t bits;

    for (;;)
    {
        Message[sizeof(Message) - 1] = local_count;
        /* Finally, use the queues*/
        /* xQueueSend... */
        xQueueSend(queue_handler, Message, portMAX_DELAY);

#ifdef USE_EVENTS_CODE
        /* Set the bit on the event group corresponding to the current count */
        bits = xEventGroupSetBits(xEvents, (1 << (local_count - 0x30)));
        LED_RED_TOGGLE();
#endif
        vTaskDelay(200);

        local_count++;
        if (local_count > '9')
        {
            local_count = '0';
        }
    }
}

void queue_receiver(void *pvParameters) {
    char localMsg[sizeof(Message)];
    /* step 2, create the queue */
    queue_handler = xQueueCreate(1, sizeof(Message));
    for (;;)
    {
        /* Finally, use the queues*/
        /* xQueueReceive... */
        xQueueReceive(queue_handler, localMsg, portMAX_DELAY);
        vTaskDelay(200);
    }
}
