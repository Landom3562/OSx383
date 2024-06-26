#include "timer.h"
#include "isr.h"
#include "monitor.h"
#include "scheduler.h"
#include "clock.h"
u32int tick = 0;
u32int globalFrequency;

#define MAX_TIMERS 10
periodic_timer_t timers[MAX_TIMERS];
u32int timer_count = 0;
u32int initial_esp;

static void timer_callback(registers_t regs)
{
    tick++;
    // monitor_write("Tick: ");
    // scheduler_wake_tasks();
    // schedule_flag = 1;
    // schedule();
    // monitor_write("Tick: ");
    // monitor_write_dec(tick);

    for (int i = 0; i < timer_count; i++)
    {
        periodic_timer_t *timer = &timers[i];
        task_t *task = &task_queue[i];
        timer->tick_count++;
        if (timer->tick_count >= timer->period)
        {
            timer->tick_count = 0;
            task->state = TASK_READY;
        }
    }
    if (tick % 10 == 0)
    {
        if (task_count == 0)
        {
            return;
        }
        task_t *currentTask = &task_queue[current_task];
        currentTask->regs.eip = regs.eip;
        currentTask->regs.esp = regs.esp;
        currentTask->regs.ebp = regs.ebp;
        // monitor_write("regs.esp: ");
        // monitor_write_dec(regs.esp);
        // monitor_put('\n');
        // monitor_write("esp: ");
        // monitor_write_dec(esp);
        // monitor_put('\n');
        // monitor_write("initial_esp: ");
        // monitor_write_dec(initial_esp);
        // monitor_put('\n');
        // asm volatile("mov %0, %%esp" : : "r"(regs.esp));
        // current_task = (current_task + 1) % task_count;
        // asm volatile("mov %%esp, %0" : : "r"(esp));
        // monitor_write_dec(current_task);
        // monitor_put('\n');
        // task_t* nextTask = &task_queue[current_task];
        // monitor_write_dec(nextTask->period);
        // monitor_write_dec(nextTask->regs.eip);
        // monitor_put('\n');
        // monitor_write_dec(nextTask->regs.ebp);
        // monitor_put('\n');
        // monitor_write_dec(nextTask->regs.esp);
        // monitor_put('\n');
        // context_switch(nextTask->regs.eip, nextTask->regs.ebp, nextTask->regs.esp);
        schedule();
    }
}

void init_timer(u32int frequency)
{
    register_interrupt_handler(IRQ0, &timer_callback);

    globalFrequency = frequency;

    u32int divisor = 1193180 / frequency;

    outb(0x43, 0x36);

    u8int l = (u8int)(divisor & 0xFF);
    u8int h = (u8int)((divisor >> 8) & 0xFF);

    outb(0x40, l);
    outb(0x40, h);
}

void set_timer_periodic(periodic_timer_t *timer, u32int period)
{
    timer->period = period;
    timer->tick_count = 0;
    timer->fired = 0;
    timers[timer_count++] = *timer;
}
