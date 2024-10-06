/* Standard includes.  */
#include <stdio.h>
#include <string.h>
#include <semphr.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Declaration of Binary Semaphore */
SemaphoreHandle_t xBinarySemaphore;

/* Task handlers creation. */
TaskHandle_t myTask1Handle = NULL;
TaskHandle_t myTask2Handle = NULL;
TaskHandle_t myTask3Handle = NULL;

/* Task functions definitions */
static void myTask1( void *p );
static void myTask2( void *p );
static void myTask3( void *p );


/* Declaration of Shared Resource */
int sharedResource = 0;


/* This example shows a priority inversion problem in action: higher-priority task (task 3) is blocked because a
*  lower-priority task (task 1) holds a resource it needs and, during this time, the lower-priority task gets 
*  preempted by a medium-priority task (task 2).
*/

void main_tasks_prio_inversion(void) {
    
    /* Binary Semaphore definition */
    xBinarySemaphore = xSemaphoreCreateBinary();

    if (xBinarySemaphore != NULL) {
        /* Initially give the semaphore so task1 can take it first */
        xSemaphoreGive(xBinarySemaphore);

        
        xTaskCreate(task1, "Task 1", 200, (void*) 0, 1, myTask1Handle);
        xTaskCreate(task2, "Task 2", 200, (void*) 0, 1, myTask2Handle);
        xTaskCreate(task3, "Task 3", 200, (void*) 0, 2, myTask3Handle);

        vTaskStartScheduler();
    } else {
        
        printf("Failed to create the semaphore.\n");
    }

    /* infinite loop */

    while(1){

		/* add application code here */
	}
}


/* Task functions implementations */


void task1(void *p) {
    
    /* Memorize t1_prio for debug purposes */
    UBaseType_t t1_prio = uxTaskPriorityGet(NULL);

    while (1) {

        /* Take the semaphore to access the shared resource */
        if (xSemaphoreTake(xBinarySemaphore, portMAX_DELAY) == pdTRUE) {
        
            sharedResource++;
            printf("Task1: Shared resource incremented to %d\n", sharedResource);
            //printf("Task1 is running...prio is:   %d\r\n", t1_prio);

            t1_prio = uxTaskPriorityGet(NULL);

            /* For debug purposes print the priority of task1 while he has the semaphore*/
            //printf("Task1 is running...prio is:   %d\r\n", t1_prio);

            /* Delay task1, who has the binary semaphore! */
            vTaskDelay(pdMS_TO_TICKS(1000));

            printf("Task1: Semaphore given\n");

            t1_prio = uxTaskPriorityGet(NULL);
            printf("[Before_Giving] Task1 is running...prio is:   %d\r\n", t1_prio);

            /* Give the semaphore back */
            xSemaphoreGive(xBinarySemaphore);
            
            /* Delay task1 for 1000ms */
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
}


void task2(void *p) {
    while (1) {

        printf("Task2: Executing\n");

        /* Delay task2 for 200ms */
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}


void task3(void *p) {

    while (1) {
            
        printf("Task 3: I want to access the shared resource... \n");

        /* Try to take the semaphore to access the shared resource */
        if (xSemaphoreTake(xBinarySemaphore, portMAX_DELAY) == pdTRUE) {

            printf("Task3: Accessing shared resource\n");
            sharedResource += 2;
            printf("Task3: Shared resource incremented to %d\n", sharedResource);

            /* Give the semaphore back */
            xSemaphoreGive(xBinarySemaphore);
            printf("Task3: Semaphore given\n");
            
            /* Delay for 1000ms */
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
}


