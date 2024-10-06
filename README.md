# FreeRTOS Custom Project

This repository contains a FreeRTOS-based project with several enhancements and modifications beyond the base operating system. The project was developed as part of the *Master's in Cybersecurity* at *Politecnico di Torino* during the 2023/2024 academic year. The goal of this project is to showcase FreeRTOS features and implement additional functionalities, including custom scheduling algorithms and memory allocation mechanisms.

## Features

1. **FreeRTOS Scheduler**:
   - The base FreeRTOS scheduler supports preemptive, priority-based, and round-robin scheduling.
   - Demonstrations of various scheduling algorithms, including Rate Monotonic (RM) and custom Early Deadline First (EDF) scheduling.

2. **Priority Inversion Problem**:
   - A scenario demonstrating priority inversion and its resolution using binary and mutex semaphores for mutual exclusion. Mutex semaphores temporarily raise task priority to solve the inversion.

3. **Task Communication (Event Groups)**:
   - Multiple tasks communicate via event groups for task synchronization. Mutex semaphores and event flags are used for mutual exclusion and event-driven task synchronization.

4. **Rate Monotonic Scheduling**:
   - Implementation of RM scheduling where tasks are executed based on fixed priorities. `vTaskDelayUntil()` ensures periodic task execution with constant frequency.

## Modifications Over Base FreeRTOS

### 1. **EDF Scheduling Implementation**
   - **EDF Scheduler**: Added support for EDF scheduling, which is not available in the default FreeRTOS. EDF schedules tasks based on deadlines, running the task with the closest deadline to avoid deadline misses.
   - **New Ready List**: A new list (`xReadyTaskListEDF`) is introduced to store tasks based on their deadlines.
   - **API Extensions**: Introduced `xTaskPeriodicCreate()` for periodic task creation with a specified deadline.
   - **Task Context Switching**: Context switching is modified to allow tasks with closer deadlines to preempt other tasks.
   
### 2. **Memory Allocation Mechanisms**
   - Two new memory allocation strategies were implemented:
     - **Best Fit Algorithm**: Allocates the smallest available block that fits the request, optimizing memory use.
     - **Buddy System Allocation**: Combines small memory blocks to reduce fragmentation.
   - These are implemented in the `heap_5.c` file, allowing allocation from multiple memory spaces.

### 3. **Benchmark**
   - A benchmark comparing Rate Monotonic (RM) and EDF scheduling was performed. The results show:
     - **EDF**: Maximizes CPU utilization and handles tighter deadlines, but with increased context switches.
     - **RM**: Predictable, fixed priorities, but limited CPU utilization and more susceptible to sporadic tasks causing deadline misses.

## Tools and Setup

### Linux Setup:
1. Install QEMU and ARM toolchain.
2. Download and build the FreeRTOS source code and demo.
3. Run FreeRTOS on QEMU using the provided makefiles.

### Mac OS Setup:
1. Use Homebrew to install the ARM GCC compiler and QEMU.
2. Configure the environment and compile FreeRTOS with the provided tools.

## Directories:

- The **FreeRTOS/Source** directory contains the FreeRTOS source code, along with its own readme file.
  
- The **FreeRTOS/Demo** directory contains a customized demo application.

For full details of the directory structure and information on locating the files, see [FreeRTOS/SourceOrganization](http://www.freertos.org/a00017.html).

The easiest way to use FreeRTOS is to start with one of the pre-configured demo application projects (found in the FreeRTOS/Demo directory). This ensures that:
- The correct FreeRTOS source files are included.
- The appropriate include paths are configured.

Once a demo application is building and executing, you can remove the demo files and start adding your own application source files.

## Quick Links:
- [FreeRTOS Quick Start Guide](http://www.freertos.org/FreeRTOS-quick-start-guide.html)
- [FreeRTOS FAQ](http://www.freertos.org/FAQHelp.html)

## Conclusion

This project enhances FreeRTOS with an EDF scheduler and improved memory allocation techniques, making it more suitable for complex real-time applications. These modifications expand FreeRTOS's capabilities in environments where dynamic scheduling and memory management are critical for task management.

