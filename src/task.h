#ifndef TASK_H
#define TASK_H

#include "common.h"
#include "isr.h"

typedef void (*task_func_t)(void*);

typedef enum task_state {
    TASK_RUNNING,
    TASK_READY,
    TASK_WAITING,
    TASK_TERMINATED
} task_state_t;

typedef struct task {
    void (*entry)(void*);
    void *arg;
    u32int stack_size;
    int priority;
    task_state_t state;
    u32int *stack;
    u32int *sp;
    registers_t regs;
    int time_until_next_run;
} task_t;

void task_create(task_t *task);

#endif // TASK_H