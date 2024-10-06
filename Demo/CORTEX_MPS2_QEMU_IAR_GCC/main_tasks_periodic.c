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
 * In the example main_tasks_delay the two tasks are periodic, but using vTaskDelay()
 * does not guarantee that the frequency at which they run is fixed, as the time
 * at which the tasks leave the blocked state is relative to when they call 
 * vTaskDelay(). Converting the tasks to use vTaskDelayUntil() solves this
 * potential problem
*/


/* 
 * Main function
 * Two tasks are created. Task 1 has a higher priority than Task2. A task 
 * enters in blocked state after it prints something. This allows the scheduler
 * to run the other task if it's in ready state (otherwise the idle task will be
 * executed)
 */

void main_tasks_periodic( void )
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
	
	TickType_t lastWakeTime; 

	int count = 0;
/*
 * The LastWakeTime variable need to be initialized with the current tick count.
 * This is the only time the variable is written explicitly.
 * After this, it will be automatically updated within vTaskDelayUntil()
*/
	lastWakeTime = xTaskGetTickCount();

	while(1)
	{
		
		printf("Task1, my counter displays:  %d\r\n", count++);
/*
 * This task should execute every 300ms exactly
*/
		vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(300));
	}
}

static void myTask2 (void *p)
{
	(void) p;
	
	TickType_t lastWakeTime;

	int count = 0;
	lastWakeTime = xTaskGetTickCount();
	while(1)
	{
		printf("Task2, my counter displays:  %d\r\n", count++);
		vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(200));
		
	}


}


