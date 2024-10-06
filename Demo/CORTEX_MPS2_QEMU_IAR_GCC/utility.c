#include "FreeRTOS.h"
#include "stdio.h"
#include "utility.h"



/* Function to check the schedulability of the system
*/

BaseType_t isSchedulable(float task1_C, float task1_T, float task2_C, float task2_T) {
    char buffer[50];
    // Calc the CPU utilization
    float utilization = (task1_C / task1_T) + (task2_C / task2_T) ;
    itoa((int) (10000 * utilization), buffer, 10); // 10 è la base decimale

    // Check the schedulability
    if (utilization <= 1.0) {
        printf("Utilization factor: %c%c.%c%c\n", buffer[0], buffer[1], buffer[2], buffer[3]);
        printf("FEASIBLE CPU UTILIZATION.\n");
        
        return pdTRUE;  // The system is schedulable
    } else {
        printf("Utilization factor: %c%c.%c%c\n", buffer[0], buffer[1], buffer[2], buffer[3]);
        printf("NOT FEASIBLE CPU UTILIZATION.\n ");
        return pdFALSE; // The system is not schedulable
    }
}
