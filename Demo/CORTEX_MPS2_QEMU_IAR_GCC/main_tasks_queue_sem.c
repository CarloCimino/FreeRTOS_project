/* Standard includes.  */
#include <stdio.h>
#include <string.h>
#include <queue.h>
#include <semphr.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Queue declaration */
QueueHandle_t queue;

/* Semaphores declarion */
SemaphoreHandle_t xSemaphore;
SemaphoreHandle_t xCountingSemaphore;

/* Task handlers creation. */
TaskHandle_t myTask1Handle = NULL;
TaskHandle_t myTask2Handle = NULL;
TaskHandle_t myTask3Handle = NULL;

/* Task functions definitions */

static void myTask1( void *p );
static void myTask2( void *p );
static void myTask3( void *p );

/* The example is exaclty like the one in "main_tasks_queue.c", but 
 * since the queue is a global object accessible by the tasks sempahores
 * has been added in the code (for mutual exclusion over shared resource)
 */

void main_tasks_queue_sem(void) {

    queue = xQueueCreate(10, sizeof(int));

    if (queue != NULL) {
        /* Semaphores definition */
        /*Mutex semaphore for mutual access to shared resource*/
        xSemaphore = xSemaphoreCreateMutex(); 
        /* Couting semaphore to indicate the number of slots in the queue available */
        xCountingSemaphore = xSemaphoreCreateCounting(10, 0);

        if (xSemaphore != NULL && xCountingSemaphore != NULL) {
            
            xTaskCreate(task1, "Task 1", 200, (void*) 0, 1, myTask1Handle);
            xTaskCreate(task2, "Task 2", 200, (void*) 0, 1, myTask2Handle);
            xTaskCreate(task3, "Task 3", 200, (void*) 0, 2, myTask3Handle);

          
            vTaskStartScheduler();
        } else {
            
            printf("Failed to create the semaphores.\n");
        }
    } else {
        
        printf("Failed to create the queue.\n");
    }
    /* infinite loop */

    while(1){

		/* add application code here */
	}
}


/* Task functions implementations */

void task1(void *p) {
    int counter = 0;
    while (1) {
        counter++;
        /* Before accessing the shared queue, take the semaphore */
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
            
            if (xQueueSend(queue, &counter, portMAX_DELAY) == pdPASS) {
                printf("Task1 sent: %d\n", counter);
                /* Notify Task3 that a new element has been put in the queue*/
                xSemaphoreGive(xCountingSemaphore);
            }
            /* Release the semaphore */
            xSemaphoreGive(xSemaphore);
        }
        /* Delay for 100ms */
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}


void task2(void *p) {
    int counter = 100;
    while (1) {
        counter++;
       /* Before accessing the shared queue, take the semaphore */
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
            
            if (xQueueSend(queue, &counter, portMAX_DELAY) == pdPASS) {
                printf("Task2 sent: %d\n", counter);
               /* Notify Task3 that a new element has been put in the queue*/
                xSemaphoreGive(xCountingSemaphore);
            }
           /* Release the semaphore */
            xSemaphoreGive(xSemaphore);
        }
        /* Delay for 50ms */
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}


void task3(void *p) {
    int receivedNum;
    TickType_t xLastWakeTime;
    const TickType_t xPeriod = pdMS_TO_TICKS(250);

    
    xLastWakeTime = xTaskGetTickCount();

    while (1) {
       
       /* Delay for period time of 250ms*/
        vTaskDelayUntil(&xLastWakeTime, xPeriod);

        /* If the queue is not empty, take the elements from the queue */
        while (uxQueueMessagesWaiting(queue) > 0) {
            if (xQueueReceive(queue, &receivedNum, 0) == pdPASS) {
                printf("Task3 received: %d\n", receivedNum);
            }
        }
    }
}
