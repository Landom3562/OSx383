#include "monitor.h"
#include "descriptor_tables.h"
#include "isr.h"
#include "kb.h"
#include "scheduler.h"
#include "timer.h"
#include "clock.h"

/*
static void isr3_callback(registers_t regs)
{
    monitor_write("This is interrupt service routine 3 \n");

}*/

void Task1(void *arg){
    int u = 30;
    // asm volatile("cli");
    // monitor_write("Geliyorum\n");
    // asm volatile("sti");
    // task_t* task = &task_queue[0];
    // task_t* nextTask = &task_queue[1];
    periodic_timer_t timer;
    set_timer_periodic(&timer, 500);
    while (1){
        //for(int i = 0; i < 10000000000; i++);
        asm volatile("cli");
        monitor_write("Task1:");
        monitor_write_dec(u++);
        monitor_put('\n');
        asm volatile("sti");
        // monitor_write_dec(esp);
        // monitor_put('\n');
        // monitor_write_dec(ebp);
        // monitor_put('\n');
        // monitor_write_dec(eip);
        // monitor_put('\n');

        //for(int q = 0; q < 1000000000; q++);
        // u32int esp; 
        // asm volatile("movl %%esp, %0" : "=r"(esp));
        // u32int ebp; 
        // asm volatile("movl %%ebp, %0" : "=r"(ebp));
        // task->regs.eip = eip;
        // task->regs.ebp = ebp;
        // task->regs.esp = esp;
        // context_switch(nextTask->regs.eip, nextTask->regs.ebp, nextTask->regs.esp);

        wait_timer_event(2);
        //monitor_write("Tell schrodinger that I have survived: TASK1\n");
    }
}
void Task2(void *arg){
    //set_timer_periodic();
    // asm volatile("cli");
    // monitor_write("Geldim geldiiim\n");
    // asm volatile("sti");
    int i = 0;
    int j = 0;
    // task_t* task = &task_queue[1];
    // task_t* nextTask = &task_queue[0];
    // u32int eip;
    // u32int test_eip = read_eip();
    // if(test_eip != 0x12345){
    //     eip = test_eip;
    // }
    periodic_timer_t timer;
    set_timer_periodic(&timer, 300);
    while(1){
        //for(int i = 0; i < 10000000000; i++);
        asm volatile("cli");
        monitor_write("Task2:");
        monitor_write_dec(j++);
        monitor_put('\n');
        asm volatile("sti");
        //for(int q = 0; q < 1000000000; q++);
        // u32int esp; asm volatile("movl %%esp, %0" : "=r"(esp));
        // u32int ebp; asm volatile("movl %%ebp, %0" : "=r"(ebp));
        // task->regs.eip = eip;
        // task->regs.ebp = ebp;
        // task->regs.esp = esp;
        // context_switch(nextTask->regs.eip, nextTask->regs.ebp, nextTask->regs.esp);

        wait_timer_event(1);
        //monitor_write("Tell schrodinger that I have survived: TASK2\n");
    }
}
void Task3(void *arg){
    int i = 0;
    periodic_timer_t timer;
    set_timer_periodic(&timer, 100);
    while(1){
        asm volatile("cli");
        monitor_write("TASK3:");
        monitor_write_dec(i++);
        monitor_put('\n');
        wait_timer_event(0);
    }
}


int main(struct multiboot *mboot_ptr, u32int initial_stack)
{
    initial_esp = initial_stack;
    init_descriptor_tables();
    monitor_clear();
    monitor_write("Welcome to OSx383.\n");
    monitor_write_colored("OSx383>", 0x0, 0x3);
    // monitor_write("OK\n");
    
    //register_interrupt_handler(3, &isr3_callback);

    //asm volatile("int $0x3");
    //asm volatile("int $0x4");

    char arg1 = 'c';
    task_t task1 = { Task1, &arg1, 1024, 1 };
    //task_create(&task1);
    scheduler_add_task(&task1);

    char arg2 = 'e';
    task_t task2 = { Task2, &arg2, 1024, 2 };
    //task_create(&task2);
    scheduler_add_task(&task2);

    char arg3 = 'a';
    task_t task3 = { Task3, &arg3, 1024, 3 };
    //task_create(&task3);
    scheduler_add_task(&task3);

    keyboard_install();
    init_clock();
    init_timer(1000);

    task_t* startTask = &task_queue[0];
    context_switch(startTask->regs.eip, startTask->regs.ebp, startTask->regs.esp);
    asm volatile("sti");
    
    // monitor_write_dec(startTask->regs.eip);
    // monitor_put('\n');
    // monitor_write_dec(startTask->regs.ebp);
    // monitor_put('\n');
    // monitor_write_dec(startTask->regs.esp);
    // monitor_put('\n');
    // monitor_write("Gelecek msin\n");
    // context_switch(startTask->regs.eip, startTask->regs.ebp, startTask->regs.esp);
    // monitor_write("Gelecek myim\n");
    //startTask->entry(task_queue[0].arg);

    // while(1){
    //     schedule();
    // }

    return 0xDEADBABA;
}

