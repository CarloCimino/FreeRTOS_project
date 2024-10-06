/* Standard includes.  */
#include <stdio.h>
#include <string.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Task handlers creation. */
TaskHandle_t myTask1Handle = NULL;
TaskHandle_t myTask2Handle = NULL;
TaskHandle_t myTask3Handle = NULL;

/* Task functions definitions*/

static void myTask1( void *p );
static void myTask2( void *p );
static void myTask3( void *p );

/*
 * Previous examples have examined the bahavior of both polling and blocking tasks
 * is isolation. Now we will mix the two scenarios by having both blocking tasks
 * and non-blocking tasks
*/


/* 
 * Main function
 * Two non blocking tasks (task1 and task2) are created with priority 1. These
 * do nothing other than just continuously print something. Task3, whose priority
 * is 2, periodically prints something
 */

void main_tasks_mixed( void )
{

	xTaskCreate(myTask1, "task1", 200, (void*) 0, tskIDLE_PRIORITY+1, &myTask1Handle);
	xTaskCreate(myTask2, "task2", 200, (void*) 0, tskIDLE_PRIORITY+1, &myTask2Handle);
	xTaskCreate(myTask3, "task3", 200, (void*) 0, tskIDLE_PRIORITY+2, &myTask3Handle);

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

	const TickType_t delay200ms = pdMS_TO_TICKS(200); 

	while(1)
	{
		printf("Task1 says no problems occurred:  \r\n");
		vTaskDelay(delay200ms);
	}
}

static void myTask2 (void *p)
{
	(void) p;
	
	const TickType_t delay200ms = pdMS_TO_TICKS(200); 
	
	while(1)
	{
		printf("Task2 says no problems occurred: \r\n");
		vTaskDelay(delay200ms);
	}

}


static void myTask3 (void *p)
{
	(void) *p;
	TickType_t lastWakeTime;
	
	lastWakeTime = xTaskGetTickCount();
	while(1)
	{
		printf("---***---\n");
		printf("Task3 periodically asking if any problem occurred: \r\n");
		printf("---***---\n");
		vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(500));
	}
	
}

