/*
 * queues.h
 *
 *  Created on: 06/09/2016
 *      Author: rperalez
 */

#ifndef SOURCE_QUEUES_H_
#define SOURCE_QUEUES_H_

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

extern TaskHandle_t queue_tx_task_handler;
extern TaskHandle_t queue_rx_task_handler;
/* step 1, declare the queue handler */
extern QueueHandle_t queue_handler;

extern void queue_sender(void *pvParameters);
extern void queue_receiver(void *pvParameters);

#endif /* SOURCE_QUEUES_H_ */
