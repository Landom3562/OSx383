#include "monitor.h"
#include "shell.h"
#include "clock.h"
char* commands[] = {"help", "settime", "reboot", "\0"}; 

void execute_command(char* command){
    char extractSettime[] = {command[0],command[1],command[2],command[3],command[4],command[5],command[6], '\0'};
    // monitor_write(extractSettime);
    if(strcmp(command, "help") == 0){
        monitor_write_colored("Available commands: ",0x0,0xF);
        for(int i = 0; strcmp(commands[i], "\0") != 0; i++){
            monitor_write_colored(commands[i], 0x0,0xF);
            monitor_write_colored(", ",0x0,0xF);
        }
        monitor_write_colored("\b\b",0x0,0xF); //To delete the last comma.
        monitor_put_colored('\n', 0x0, 0xF);

    }else if(strcmp(extractSettime, "settime") == 0){
        u8int hour = (command[8] - 48) * 10 + (command[9] - 48);
        u8int minute = (command[11] - 48) * 10 + (command[12] - 48); 
        u8int second = (command[14] - 48) * 10 + (command[15] - 48);
        if(hour < 24 && minute < 60 && second < 60){
            set_time(hour,minute,second);
        }else{
            monitor_write_colored("Usage: settime hh mm ss\n",0x0,0xF);
        }
    }else if(strcmp(command, "reboot") == 0){
        monitor_write_colored("Rebooting...",0x0,0xF);
        monitor_clear();
        asm volatile(
            "wait1:\n"
            "inb $0x64, %%al\n"   
            "testb $0x02, %%al\n" 
            "jne wait1\n"

            "movb $0xFE, %%al\n" 
            "outb %%al, $0x64\n"
            :
            :
            : "al");
    }else{
        monitor_write_colored(command,0x0,0xF);
        monitor_write_colored(" is an invalid command.\n",0x0,0xF);
        monitor_write_colored("Type 'help' for a list of available commands.\n",0x0,0xF);
    }
}