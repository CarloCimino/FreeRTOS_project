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
 * Two tasks are created. Task 1 has a higher priority than Task2.This means 
 * Task1 will be always running, while Task2 will be always in the ready state
 * (starving because he won't be ever scheduled)
 */

void main_tasks_priority( void )
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

	int count = 0;
	while(1)
	{
		printf("Task1, my counter displays:  %d\r\n", count++);
		
		for(int i=0; i< 1000; i++){
			/* Bad delay implementation*/
		}
	}
}

static void myTask2 (void *p)
{
	(void) p;

	int count = 0;
	while(1)
	{
		printf("Task2, I take more time:  %d\r\n", count++);
		
		for(int i=0; i< 1500; i++){
			/* Bad delay implementation*/
		}
	}


}


