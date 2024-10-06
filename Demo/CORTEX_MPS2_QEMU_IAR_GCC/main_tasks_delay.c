/* Standard includes.  */
#include <stdio.h>
#include <string.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Task handlers creation. */
TaskHandle_t myTask1Handle = NULL;
TaskHandle_t myTask2Handle = NULL;

/* Task functions definitions*/

static void myTask1( void *p );
static void myTask2( void *p );

/* 
 * Main function
 * Two tasks are created. Task 1 has a higher priority than Task2. A task 
 * enters in blocked state after it prints something. This allows the scheduler
 * to run the other task if it's in ready state (otherwise the idle task will be
 * executed)
 */

void main_tasks_delay( void )
{

	xTaskCreate(myTask1, "task1", 200, (void*) 0, tskIDLE_PRIORITY+2, &myTask1Handle);
	xTaskCreate(myTask2, "task2", 200, (void*) 0, tskIDLE_PRIORITY+1, &myTask2Handle);

	vTaskStartScheduler();
	/* infinite loop */

	while(1){

		/* add application code here */
	}
}

/* Task functions implementations */

static void myTask1 (void *p)
{
	(void) p;
	
	/* Use a macro to convert time into an equivalent time in ticks */
	const TickType_t delay200ms = pdMS_TO_TICKS(200); 

	int count = 0;
	while(1)
	{
		printf("Task1, my counter displays:  %d\r\n", count++);
/*
 * Delay for a period. This time we use vTaskDelay() which places the task into
 * the blocked state until the delay period has expired. The functions takes as
 * parameter a time specified in "ticks"
 */
		vTaskDelay(delay200ms);
	}
}

static void myTask2 (void *p)
{
	(void) p;
	
	const TickType_t delay100ms = pdMS_TO_TICKS(100); 

	int count = 0;
	while(1)
	{
		printf("Task2, my counter displays:  %d\r\n", count++);
		vTaskDelay(delay100ms);
		
	}


}


