#include "scheduler.h"

task_t task_queue[MAX_TASKS];
int task_count = 0;
int current_task = 0;
int next_task = -1;
// u8int schedule_flag = 1;

u8int task_stacks[MAX_TASKS][STACK_SIZE];

extern initial_esp;

// static inline void save_context(registers_t *regs) {
//     asm volatile("movl %%esp, %0" : "=r"(regs->esp));
//     asm volatile("movl %%ebp, %0" : "=r"(regs->ebp));
// }

// static inline void restore_context(registers_t *regs) {
//     asm volatile("movl %0, %%esp" : : "r"(regs->esp));
//     asm volatile("movl %0, %%ebp" : : "r"(regs->ebp));
// }

void scheduler_add_task(task_t *task)
{

    if (task_count < MAX_TASKS)
    {
        task->stack = task_stacks[task_count];
        // memset(task->stack, 0, task->stack_size);
        // task->sp = task->stack + STACK_SIZE;
        // *(--task->sp) = (u32int)task->arg;  // Pass argument to task function
        // *(--task->sp) = (u32int)task->entry; // Return address (task function entry point)
        // *(--task->sp) = 0x200;  // EFLAGS
        // *(--task->sp) = 0x08;   // CS (Code Segment)
        asm volatile("cli");
        task->regs.esp = (u32int)(task->stack + STACK_SIZE);
        task->regs.ebp = (u32int)(task->stack + STACK_SIZE);
        task->regs.eip = (u32int)task->entry;
        // monitor_write_dec((u32int)(task->stack + STACK_SIZE));
        // monitor_put('\n');
        // monitor_write_dec((u32int)(task->stack + STACK_SIZE));
        // monitor_put('\n');
        // monitor_write_dec((u32int)task->entry);
        // monitor_put('\n');
        task->state = TASK_READY;

        // task_queue[task_count] = *task;
        // task_count++;

        int i = task_count - 1;
        while (i >= 0 && task_queue[i].priority < task->priority)
        {
            task_queue[i + 1] = task_queue[i];
            i--;
        }
        task_queue[i + 1] = *task;
        task_count++;
        asm volatile("sti");
    }
}
// It is assumed that the contents of the task is already saved.
void schedule()
{
    asm volatile("cli");
    // schedule_flag = 0;
    if (task_count == 0)
    {
        return;
    }

    // monitor_write_dec(esp);
    // monitor_put('\n');
    // monitor_write_dec(ebp);
    // monitor_put('\n');
    // monitor_write_dec(eip);
    // monitor_put('\n');

    int max_priority = -1;
    int max_priority_task = -1;
    for (int i = 0; i < task_count; i++)
    {
        task_t *task = &task_queue[i];
        if (task->state == TASK_READY)
        {
            if (task->priority > max_priority)
            {
                max_priority = task->priority;
                max_priority_task = i;
            }
        }
    }

    next_task = max_priority_task;
    // if(next_task < 0){
    //     monitor_write("No task to run\n");
    //     return;
    // }

    task_t *next = &task_queue[next_task];
    u32int esp = next->regs.esp;
    u32int ebp = next->regs.ebp;
    u32int eip = next->regs.eip;
    // monitor_write_dec(current_task);
    // monitor_put('\n');
    // monitor_write_dec(esp);
    // monitor_put('\n');
    // monitor_write_dec(ebp);
    // monitor_put('\n');
    // monitor_write_dec(eip);
    // monitor_put('\n');

    if (eip == 0x12345)
    {
        return;
    }
    // monitor_write("Switching context\n");
    if (next->state == TASK_READY)
    {
        next->state = TASK_RUNNING;
        //monitor_write_dec(next->priority);
        current_task = next_task;
        context_switch(eip, ebp, esp);
    }
    else
    {
        // monitor_write("Task is not ready\n");
        // schedule();
    }
    // next->state = TASK_RUNNING;
    // context_switch(eip,ebp,esp);
    asm volatile("sti");
}

void wait_timer_event(int task_id)
{
    task_t *task = &task_queue[task_id];
    task->state = TASK_WAITING;
    // asm volatile("int $0x2A");
    u32int esp;
    asm volatile("mov %%esp, %0" : "=r"(esp));
    u32int ebp;
    asm volatile("mov %%ebp, %0" : "=r"(ebp));
    u32int eip = read_eip();
    // monitor_write_dec(esp);
    if (eip == 0x12345)
    {
        return;
    }
    task->regs.esp = esp;
    task->regs.ebp = ebp;
    task->regs.eip = eip;
    while (task->state == TASK_WAITING)
    {
        schedule();
    }
    // monitor_write("Task is awake\n");
}
