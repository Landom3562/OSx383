#include "clock.h"
#include "scheduler.h"

#define CMOS_RTC_ADDRESS 0x70
#define CMOS_RTC_DATA 0x71

u8int currentTime[6];

static void clock_callback(registers_t regs)
{
    write_time();
    //To clear the C register for the next interrupt to be generated
    outb(CMOS_RTC_ADDRESS, 0x0C);
    inb(CMOS_RTC_DATA);
}

void init_clock()
{
    register_interrupt_handler(IRQ8, &clock_callback);

    //To enable periodic interrupts. Default rate is 1024 Hz
    outb(CMOS_RTC_ADDRESS, 0x0B);
    char prev = inb(CMOS_RTC_DATA);
    outb(CMOS_RTC_ADDRESS, 0x0B);
    outb(CMOS_RTC_DATA, prev | 0x40);
}

void write_time(){
    get_time();
    monitor_display_clock_colored(currentTime, 0x7, 0xE);
}

void get_time(){
    u8int t, regB;
    //24 hour mode and BCD mode activation
    asm volatile("cli");
    outb(CMOS_RTC_ADDRESS, 0x0B);
    regB = inb(CMOS_RTC_DATA);
    regB = regB | 0x06; 
    outb(CMOS_RTC_ADDRESS, 0x0B);
    outb(CMOS_RTC_DATA, regB);
    asm volatile("sti");
    for(int i = 5; i > 0; i = i-2){
        asm volatile("cli");
        outb(CMOS_RTC_ADDRESS, 5 - i);
        t = inb(CMOS_RTC_DATA);
        asm volatile("sti");
        currentTime[i] = (t % 10) + 48;
        currentTime[i-1] = (t/10) + 48;
    }
}

void set_time(u8int hour, u8int minute, u8int second){
    u8int regB;
    asm volatile("cli");
    outb(CMOS_RTC_ADDRESS, 0xB);
    regB = inb(CMOS_RTC_DATA);
    regB = regB | 0x06;
    outb(CMOS_RTC_ADDRESS, 0x0B);
    outb(CMOS_RTC_DATA, regB);
    outb(CMOS_RTC_ADDRESS, 0);
    outb(CMOS_RTC_DATA, second);
    outb(CMOS_RTC_ADDRESS, 2);
    outb(CMOS_RTC_DATA, minute);
    outb(CMOS_RTC_ADDRESS, 4);
    outb(CMOS_RTC_DATA, hour);
    asm volatile("sti");
    monitor_write_colored("Time has been set to: ",0x0,0xF);
    monitor_put_colored(hour / 10 + 48,0x0,0xF);
    monitor_put_colored(hour % 10 + 48,0x0,0xF);
    monitor_put_colored(':',0x0,0xF);
    monitor_put_colored(minute / 10 + 48,0x0,0xF);
    monitor_put_colored(minute % 10 + 48,0x0,0xF);
    monitor_put_colored(':',0x0,0xF);
    monitor_put_colored(second / 10 + 48,0x0,0xF);
    monitor_put_colored(second % 10 + 48,0x0,0xF);
    monitor_put_colored('\n',0x0,0xF);
}