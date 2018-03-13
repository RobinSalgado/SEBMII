#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"

void print1_task(void *arg)
{
	for(;;)
	{
		PRINTF("\rThis is a useless message!\n");
		vTaskDelay(rand()%10);
	}
}

void print2_task(void *arg)
{
	char *msg = (char*)arg;
	for(;;)
	{
		xSemsphoreTake(mutex_uart, portMAX_DELAY);
		PRINTF("\rAnother useless message here!\n");
		xSemaphoreGive(mutex_uart);
		vTaskDelay(rand()%10);
	}
}

int main(void)
{
	const char msg1[] = "\rThis is a useless message!\n";
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_InitDebugConsole();
    srand(0x15458523);


    //if we put the same parameter in two task they will execute the same function body
    //print1_task is the Pvparameter its a 32 bits variable
    xTaskCreate(print1_task, "print1", 110, (void*)msg1, configMAX_PRIORITIES, NULL);
    xTaskCreate(print2_task, "print2", 110, NULL, configMAX_PRIORITIES-1, NULL);
    vTaskStartScheduler();
    for(;;)
    {

    }
    return 0 ;
}
