/* Standard includes.  */
#include <stdio.h>
#include <string.h>
#include <semphr.h>
#include <event_groups.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Event group bits */
#define EVENT_NEW_DATA        (1 << 0)
#define EVENT_CRITICAL_TEMP   (1 << 1)

/* Declaration of mutex  handler */
SemaphoreHandle_t xMutex;

/* Declaration of even group handler */
EventGroupHandle_t xEventGroup;

/* A task event group is a synchronization mechanism that allows tasks to communicate and synchronize using 
*  event flags. An event group contains a set of bits (event flags) that tasks can set, clear, or wait for,
*  enabling tasks to signal events to each other and synchronize their operations based on these events.
*/

/* Task handlers creation. */
TaskHandle_t myTaskTempMonitorHandle = NULL;
TaskHandle_t myTaskTempProcessorHandle = NULL;
TaskHandle_t myTaskTempLoggerHandle = NULL;
TaskHandle_t myTaskTempIncrementerHandle = NULL;


/* Task functions definitions */
static void Task_CriticalTempMonitor( void *p );
static void Task_TemperatureProcessor( void *p );
static void Task_TemperatureLogger( void *p );
static void Task_TemperatureIncrementer( void *p );

/* Global variable for critical temperature */
int criticalTemp = 100;

/* The main function create 4 tasks. They use a eventGroup for communication and synchronization.
 * The tasks access a shared global variable, so semaphores are used for mutual exclusion
 * Task1 (TemperatureIncrementer) has the lowest priority(1) periodically increments the shared variable  
 * and set the event bits for NEW_DATA available.
 * Task2 (TemperatureIncrementer) has the lowest priority (1) and he just periodically prints
 * the value of the shared variable representing critical temperature
 * Task3 (TemperatureProcessor) has mid priority (2) and he checks if bits of the eventGroup are
 * set to 1. NEW_DATA is 1, then process the new temperature (prints the value); if also CRITICAL_TEMP
 * is set to 1, it handles the high temperaute by resetting the value of the shared variable
 * Task 4 (CriticalTempMonitor) is the one responsible for generating the even CRITICAL_TEMP by 
 * periodically checking the value of the shared variable: if it's > 200 it will generate the event.
 */

int main_tasks_event_group(void) {
    /* Event Group definition */
    xEventGroup = xEventGroupCreate();
    
    /* Mutex Definition */
    xMutex = xSemaphoreCreateMutex();
    
    if (xEventGroup != NULL && xMutex != NULL) {
        
        xTaskCreate(Task_CriticalTempMonitor, "Critical Temp Monitor", 200, (void*) 0, 3, myTaskTempMonitorHandle);
        xTaskCreate(Task_TemperatureProcessor, "Temperature Processor", 200, (void*) 0, 2, myTaskTempProcessorHandle);

        xTaskCreate(Task_TemperatureLogger, "Temperature Logger", 200, (void*) 0, 1, myTaskTempLoggerHandle);
        xTaskCreate(Task_TemperatureIncrementer, "Temperature Incrementer", 200, (void*) 0, 1, myTaskTempIncrementerHandle);
        
        vTaskStartScheduler();
    }
    
     /* infinite loop */
    while(1){

		/* add application code here */
	}
}

/* Task functions implementations */

void Task_CriticalTempMonitor(void *p) {
    while (1) {
        xSemaphoreTake(xMutex, portMAX_DELAY);
        if (criticalTemp >= 200) {
            /* Signal the temperature processor task */
            xEventGroupSetBits(xEventGroup, EVENT_NEW_DATA | EVENT_CRITICAL_TEMP);
            printf("[Task4] Critical Temp Monitor: New critical temperature reading: %d\n", criticalTemp);
        } else {
            printf("[Task4] Critical Temp Monitor: No overheat detected, current temperature: %d\n", criticalTemp);
        }
        xSemaphoreGive(xMutex);
        
        /* Delay for 1000ms */
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void Task_TemperatureProcessor(void *p) {
    while (1) {
        /* Wait for the new data event */
        EventBits_t uxBits = xEventGroupWaitBits(
            xEventGroup,
            EVENT_NEW_DATA | EVENT_CRITICAL_TEMP,
            pdTRUE,  // Clear bits on exit
            pdFALSE, // Wait for any bit
            portMAX_DELAY
        );
        
        if ((uxBits & EVENT_NEW_DATA) != 0) {
            /* Process the temperature data */
            printf("[Task3] Temperature Processor: Processing new temperature data\n");
        }
        
        /* If critical temperature event occurred, handle it */
        if ((uxBits & EVENT_CRITICAL_TEMP) != 0) {
            printf("[Task3] Temperature Processor: Handling critical temperature event\n");
            xSemaphoreTake(xMutex, portMAX_DELAY);
            criticalTemp = 100; // Decrease criticalTemp back to 100
            xSemaphoreGive(xMutex);
        }
    }
}

void Task_TemperatureLogger(void *p) {
    while (1) {
        xSemaphoreTake(xMutex, portMAX_DELAY);
        /* Log the processed temperature data */
        printf("[Task2] Temperature Logger: Current temperature: %d\n", criticalTemp);
        xSemaphoreGive(xMutex);
        
        /* Delay for 200ms */
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void Task_TemperatureIncrementer(void *p) {
    while (1) {
        xSemaphoreTake(xMutex, portMAX_DELAY);
        criticalTemp += 20;
        printf("[Task1] Temperatura incrementata: %d\n", criticalTemp);

        xSemaphoreGive(xMutex);

        /* Set the new data event bit */
        xEventGroupSetBits(xEventGroup, EVENT_NEW_DATA);
        /* Delay for 500ms */
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}