<link rel="stylesheet" href="../styles.css">

# RTOS ⏰
Real-Time Operating System (RTOS)


## Operating Systems
You've probably heard of the following operating systems: Mac, Windows, IOS, Android. These are **systems that run on your computer or microcontroller** that **manage when tasks** are executed such as opening Chrome, manage reading and writing to files, and interacting with external devices. Imagine if we didn't have operating systems to do these tasks. If you wanted to open Chrome to Google something, your device wouldn't know what task to prioritize. Should it prioritize moving your cursor, download that app you wanted, or open the browser? **With all this confusion, we can expect one thing: lag!** No one likes lag, that's why we use operating systems to manage our tasks.

### Scheduling

There are **different ways to schedule tasks on the microprocessor**. These can be split into two categories: **Preemptive and Non-preemptive.**

<p align="center">
<img src="../images/CPU-Scheduling-2.png" alt="Different categories of scheduling ways. Source: https://www.geeksforgeeks.org/operating-systems/cpu-scheduling-in-operating-systems/" width=70% >
<p align="center">Different categories of scheduling ways.</p>
</p>

**_Preemptive_** scheduling means the OS is allowed to interrupt a task and switch to a higher priortiy one. 

**_Non-preemptive_** scheduling means the task runs until it goes to completetion or willingly gives up it's space. 

Both have their benefits and drawbacks:
For preemptive scheduling, it prevents one process from hogging the compute power. But it can stave lower-priority processes (meaning they don't get to run). While non-preemeptive scheduling is easier to implement, one process can hog the compute power. This can lead to a denial of service attack.

### Memory

We have a type of memory called the RAM (Random access memory) that is a short term workspace. When running a program, we use RAM. In the RAM, we have the stack, heap, and static portions of memory. 

<p align="center">
<img src="../images/RAM.png" alt="Photo of RAM. Source: https://www.youtube.com/watch?v=Qske3yZRW5I&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz&index=4" width=20% >
<p align="center">Photo of RAM.</p>
</p>

The **stack is a last-in-first-out system (like a stack of pancakes)** (LIFO), while the heap is a **first-in-first-out system (like a line at a grocery store)** (FIFO). The **static portion stores our variables**. This **memory is permanent and is allocated before the program runs**. For any memory we want to **dynamically** add when we are running our program, that is added onto the **heap**. When running freeRTOS, if we create a **thread**, that is added onto the **heap**. Queues and semaphores are also added onto the heap. However, you can configure more senstive stuff from the heap onto the static portion of memory. There are different ways to manage the heap memory. Main goal of memory management is to ensure we don't run out of heap or stack memory.

### Race Conditions

Let's say we have multiple tasks that are all editing the same variable. If one tasks starts editing the variable and then is stopped before finishing, the second task will start editing and that will corrupt the data. Data corruption is bad. This is called a **race condition**

To prevent multiple tasks from editing the same variable we can use **queues, mutexes, and semaphores**. 
A queue is just like a line at a grocery store. The first task that comes in is the first task out (FIFO). You serve the first costumer before moving onto the next. This ensures that the groceries don't get mixed up. Adding tasks to the queue is atomic meaning it can't be interrupted and corrupted when it is occuring. Also, the **whole value of the task is added to the queue instead of just a reference**. Pointers can cause problems. This ensures that only 
When running tasks on freeRTOS, the priority matters. Tasks with higher priority take precedence and run over tasks with lower priority. The tasks with the highest priority are hardware interrupts. If there are multiple hardware interrupts, that's called nested interrupts and the priority scheduling depends on the device you're using.
If you have multiple cores, different tasks can run at the same time. If you have one core, the tasks will run based off scheduling. This scheduling is determined every one tick.


Why use freeRTOS? When you have many tasks you want to run and want to meet timing deadlines!

## Terminology
Task is similar to a thread

A tick is 1 millisecond




## Embedded Example with an STM32

Last Updated: September 13, 2025

Note: Working on it

Author: Khadeeja Abbas

