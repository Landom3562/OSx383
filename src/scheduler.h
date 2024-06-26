#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "task.h"

#define MAX_TASKS 10
#define STACK_SIZE 1024

extern task_t task_queue[MAX_TASKS];
extern int task_count;
extern int current_task;
extern u8int task_stacks[MAX_TASKS][STACK_SIZE];
extern u8int schedule_flag;

void scheduler_add_task(task_t *task);
void scheduler_execute_next();
void scheduler_wake_tasks();
// void scheduler_yield();
// void scheduler_start();
// void scheduler_wake_tasks();

#endif // SCHEDULER_H