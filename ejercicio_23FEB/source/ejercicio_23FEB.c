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
		vTaskDelay(rand()%10); //genera un número random entre 0 y 9
	}
}

void print2_task(void *arg)
{
	for(;;)
	{
		PRINTF("\rAnother useless message here!\n");
		vTaskDelay(rand()%10);
	}
}

int main(void)
{
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_InitDebugConsole();
    srand(0x15458523);

    xTaskCreate(print1_task, "print1", 110, NULL, configMAX_PRIORITIES, NULL);
    xTaskCreate(print2_task, "print2", 110, NULL, configMAX_PRIORITIES-1, NULL);
    vTaskStartScheduler();
    for(;;)
    {

    }
    return 0 ;
}
