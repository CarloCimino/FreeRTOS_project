/* Standard includes.  */
#include <stdio.h>
#include <string.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

#define A_PERIOD 5
#define B_PERIOD 7
#define A_CAPACITY 2
#define B_CAPACITY 4

/* Task handlers creation. */
TaskHandle_t myTask1Handle = NULL;
TaskHandle_t myTask2Handle = NULL;

/* Task functions definitions*/
static void myTask1( void *p );
static void myTask2( void *p );

/* 
 * Main function
 * Two tasks are created and scheduled with EDF algorithm.
 */

void main_tasks_edf( void )
{
/*
 * TASK 1: C = 2 T=5
 * TASK 2: C = 4 T=7
 */

	xTaskPeriodicCreate(myTask1, "task1", 200, (void*) 0, 1, myTask1Handle, 5);
    xTaskPeriodicCreate(myTask2, "task2", 200, (void*) 0, 1, myTask2Handle, 7);

	vTaskStartScheduler();
	/* infinite loop */

	while(1){

		/* add application code here */
	}
}

/* Task functions implementations */

void myTask1 (void *p)
{

    (void) p;

	TickType_t xLastWakeTimeA;

    const TickType_t xPeriod = pdMS_TO_TICKS(A_PERIOD * 1000); // task A period in ticks
	const TickType_t comp_time = pdMS_TO_TICKS(A_CAPACITY * 1000); // task A computation time in ticks

    xLastWakeTimeA = 0;

    while(1){

        TickType_t xTime = xTaskGetTickCount();

        while(xTaskGetTickCount() - xTime < comp_time)
		{

 		}
        vTaskDelayUntil( &xLastWakeTimeA, xPeriod);
    }
}

void myTask2 (void *p)
{
	(void) p;

	TickType_t xLastWakeTimeB;

	const TickType_t xPeriod = pdMS_TO_TICKS(B_PERIOD * 1000); // task B period
	const TickType_t comp_time = pdMS_TO_TICKS(B_CAPACITY * 1000); // task B computation time
	
	xLastWakeTimeB = 0;

    while(1){

        TickType_t xTime = xTaskGetTickCount();

        while(xTaskGetTickCount() - xTime < comp_time)
		{

 		}
		
        vTaskDelayUntil( &xLastWakeTimeB, xPeriod);

    }

}

