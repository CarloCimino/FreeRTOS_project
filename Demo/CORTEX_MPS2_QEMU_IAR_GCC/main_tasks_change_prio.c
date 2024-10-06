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
 * The scheduler will always select the highest ready state task as the task to
 * enter the running state. We will use vTaskPrioritySet() function to change the
 * priority of two tasks relative to each other
*/

/* 
 * Main function creates two task at two different priorities. Neither task makes
 * function calls that could cause it to enter the blocked state, so both are
 * always in either ready or running state.
 */

void main_tasks_change_prio( void )
{

	xTaskCreate(myTask1, "task1", 200, (void*) 0, 2, &myTask1Handle);
	xTaskCreate(myTask2, "task2", 200, (void*) 0, 1, &myTask2Handle);

	vTaskStartScheduler();
	/* infinite loop */

	while(1){

		/* add application code here */
	}
}

/*
 * Task1 is created with the highest priority, so is guaranteed to run first.
 * Task1 prints out a couple of strings before raising the priority of Task2 to
 * above its own priority.
 * 
 * Task2 starts to run as soon as it has the highes relative priority. Only one
 * task can be in the running state at any one time, so when Task2 is in the
 * running state, Task1 is in the ready state.
 * 
 * Task2 prints something and after that it will set its own priority back down
 * to below that of Task1. 
 * 
 * Task2 setting its priority back down means Task1 is once again the highest
 * priority task, so Task1 re-enters the running state, forcing task2 back into
 * the ready state (because the scheduler won't select it)
 * 
*/

/* Task functions implementations */

static void myTask1 (void *p)
{
	(void) p;
	
	const TickType_t delay100ms = pdMS_TO_TICKS(100); 
	
	/* returning the calling task's priority if parameter is NULL*/
	UBaseType_t t1_prio = uxTaskPriorityGet(NULL);
	UBaseType_t t2_prio = uxTaskPriorityGet(myTask2Handle);

	while(1)
	{
		printf("Task1 is running... t2 prio is:   %d\r\n", t2_prio);
		
/*
 * Setting the task2 priority above the task1 priority will cause task2 to 
 * immediately start running
*/
		vTaskPrioritySet(myTask2Handle, (t1_prio + 1));
		vTaskDelay(delay100ms);
	}
}

static void myTask2 (void *p)
{
	(void) p;
	const TickType_t delay100ms = pdMS_TO_TICKS(100); 

	UBaseType_t t1_prio = uxTaskPriorityGet(myTask1Handle);
	UBaseType_t t2_prio = uxTaskPriorityGet(NULL);

	
	while(1)
	{
		printf("Task2 is running... t1 prio is:   %d\r\n", t1_prio);

		vTaskPrioritySet(myTask1Handle, (t2_prio - 2));
		vTaskDelay(delay100ms);
	}

}


