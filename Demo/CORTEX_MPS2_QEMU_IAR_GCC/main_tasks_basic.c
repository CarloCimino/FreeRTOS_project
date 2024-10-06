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
 * Two tasks are created. Both tasks have the same priority. They are continuos
 * task, that is they can be only in two states: running or ready. They are never
 * blocked or suspended 
 */

void main_tasks_basic( void )
{
	
/*
 * The first parameter is the function that the task executes
 * The second parameter is just a decriptive name for the task
 * The third parameter is the stack size. The value specifies the number of words
 * the stack can hold. So if the word is 32-bits wide and the passed value is
 * 200, then 800 bytes of stack space will be allocated 
 * The fourth parameter is used to pass parameters to the task (typically by using
 * a pointer
 * The fifth parameter is the task's priority
 * The sixth parameter is the task handler
 */

 	xTaskCreate(myTask1, "task1", 200, (void*) 0, tskIDLE_PRIORITY+1, &myTask1Handle);
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


