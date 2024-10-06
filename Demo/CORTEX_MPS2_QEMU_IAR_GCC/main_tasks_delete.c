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
 * Two tasks are created. Task1 and Task2 share the same priority equals to 1.
 * Task2 deletes himself after some time. Deleted tasks no longer exist and 
 * cannot enter the Running state again.
 */

void main_tasks_delete( void )
{

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
	
	/* Use a macro to convert time into an equivalent time in ticks */
	const TickType_t delay200ms = pdMS_TO_TICKS(200); 

	int count = 0;
	while(1)
	{
		printf("Task1, my counter displays:  %d\r\n", count++);

		/* Delay for a period. */
		vTaskDelay(delay200ms);
	}
}

static void myTask2 (void *p)
{
	(void) p;
	
	const TickType_t delay100ms = pdMS_TO_TICKS(100); 

	int count = 10;
	while(1)
	{
		printf("Task2, my counter displays:  %d\r\n", count--);
		if(count==0){
			printf("tic tac \r\n");
			printf("BOOOOOOOOOOOOOOOOOOOOOOOOOM \r\n");
			printf("Task2 has been deleted...\n");
			/*The function vTaskDelete deletes the task whose handler is passed as parameter*/
			vTaskDelete(myTask2Handle);
		}
		vTaskDelay(delay100ms);
		
	}


}


