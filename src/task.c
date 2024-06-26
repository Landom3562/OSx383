#include "task.h"
#include "scheduler.h"
#include "common.h"

void task_create(task_t *task) {
    
    
    
    scheduler_add_task(task);
    // // Allocate stack for the task
    // task->stack_base = (u32int *)task->stack_size;

    // // Clear the allocated stack memory
    // memset(task->stack_base, 0, task->stack_size);

    // // Initialize the task's registers
    // memset(&task->regs, 0, sizeof(registers_t));

    // // Set up the initial stack frame
    // u32int *stack = (u32int *)(task->stack_base + task->stack_size);
    // *(--stack) = (u32int)task->arg;         // Argument to the task function
    // *(--stack) = 0x10;                      // ss
    // *(--stack) = (u32int)(task->stack_base + task->stack_size); // useresp
    // *(--stack) = 0x202;                     // eflags
    // *(--stack) = 0x08;                      // cs
    // *(--stack) = (u32int)task->task_func;   // eip

    // // Save the pointer to the stack in the task's register structure
    // task->regs.esp = (u32int)stack;
    // task->regs.cs = 0x08; // Kernel code segment
    // task->regs.ds = task->regs.ss = 0x10; // Kernel data segment

    // // Add the task to the scheduler
}

