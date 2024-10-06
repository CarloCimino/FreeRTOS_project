/* Standard includes.  */
#include <stdio.h>
#include <string.h>
#include <queue.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Queue declaration */
QueueHandle_t queue;

/* Task handlers creation. */
TaskHandle_t myTask1Handle = NULL;
TaskHandle_t myTask2Handle = NULL;
TaskHandle_t myTask3Handle = NULL;

/* Task functions definitions */

static void myTask1( void *p );
static void myTask2( void *p );
static void myTask3( void *p );

/* Main function creates 3 tasks. Task1 and Task2 of priority 1, while
 * task3 of priority 2. Task1 and Task2's job is to put elements
 * in the queue, while task3 empty the queue. Task3's period is higher
 * than Task1 and Task2 to allow them to fill a little the queue.
 */

void main_tasks_queue(void) {

    /* The function xQueueCreate creates a queue.
     * You can specify the number of elements it can contains 
     * and the size of the elements. 
     */

     /* Queue of 10 int elements definition */
    queue = xQueueCreate(10, sizeof(int));

    if (queue != NULL) {

        xTaskCreate(task1, "Task 1", 200, (void*) 0, 1, myTask1Handle);
        xTaskCreate(task2, "Task 2", 200, (void*) 0, 1, myTask2Handle);
        xTaskCreate(task3, "Task 3", 200, (void*) 0, 2, myTask3Handle);

        vTaskStartScheduler();

    } else {
        printf("Failed to create the queue\n");
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

        /* Send the element to the queue */
        if (xQueueSend(queue, &counter, portMAX_DELAY) == pdPASS) {
            printf("Task1 sent: %d\n", counter);
        }
        /* Delay for 100 ms */ 
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void task2(void *p) {
    int counter = 100;
    while (1) {
        counter++;
        
        /* Send the element to the queue */
        if (xQueueSend(queue, &counter, portMAX_DELAY) == pdPASS) {
            printf("Task2 sent: %d\n", counter);
        }
         /* Delay for 50 ms */ 
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void task3(void *p) {
    int receivedNum;
    TickType_t xLastWakeTime;
    const TickType_t xPeriod = pdMS_TO_TICKS(250);

    
    xLastWakeTime = xTaskGetTickCount();

    while (1) {

        vTaskDelayUntil(&xLastWakeTime, xPeriod);

        /* If the queue is not empty, take the elements from the queue*/
        while (uxQueueMessagesWaiting(queue) > 0) {
            if (xQueueReceive(queue, &receivedNum, 0) == pdPASS) {
                printf("Task3 received: %d\n", receivedNum);
            }
        }
    }
}