/* Standard includes.  */
#include <stdio.h>
#include <string.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Task handlers creation. */
TaskHandle_t myTask1Handle = NULL;
TaskHandle_t myTask2Handle = NULL;


#define A_PERIOD 5
#define B_PERIOD 7
#define A_CAPACITY 2
#define B_CAPACITY 4
/* Task functions definitions*/

static void myTask1( void *p );
static void myTask2( void *p );

/* 
 * Main function
 * Two tasks are created. Both tasks have the same priority. They are continuos
 * task, that is they can be only in two states: running or ready. They are never
 * blocked or suspended 
 */

void main_tasks_edf_prova( void )
{
/*
 * TASK 1: C = 2 T=5
 * TASK 2: C = 4 T=7
 */

	xTaskPeriodicCreate(myTask1, "task1", 500, NULL, 1, NULL, A_PERIOD);
    xTaskPeriodicCreate(myTask2, "task2", 500, NULL, 1, NULL, B_PERIOD);

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

	vTaskStartScheduler();
	/* infinite loop */

	while(1){

		/* add application code here */
	}
}

/* Task functions implementations */

void myTask1 (void *p)
{
    TickType_t xLastWakeTimeA;
    const TickType_t xFrequency = A_PERIOD;
    volatile int count = A_CAPACITY;

    xLastWakeTimeA = 0;

    while(1){

        TickType_t xTime = xTaskGetTickCount();

        TickType_t x;
        printf("[task1] executing...\n");
        while(count != 0){
            if(( x = xTaskGetTickCount()) > xTime)
            {
                xTime = x;
            }
          
        }
        count = A_CAPACITY;

        vTaskDelayUntil( &xLastWakeTimeA, xFrequency);
    }
}

void myTask2 (void *p)
{
    TickType_t xLastWakeTimeB;
    const TickType_t xFrequency = B_PERIOD;
    volatile int count = B_CAPACITY;

    xLastWakeTimeB = 0;

    while(1){

        TickType_t xTime = xTaskGetTickCount();

        TickType_t x;
        printf("[task1] executing...\n");
        while(count != 0){
            if(( x = xTaskGetTickCount()) > xTime)
            {
                xTime = x;
            }
          
        }
        count = B_CAPACITY;

        vTaskDelayUntil( &xLastWakeTimeB, xFrequency);
    }



}






