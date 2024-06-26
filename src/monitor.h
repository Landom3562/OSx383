#ifndef MONITOR_H
#define MONITOR_H

#include "common.h"

void monitor_put(char c);
void monitor_put_colored(char c, u8int backColour, u8int foreColour);
void monitor_clear();
void monitor_write(char *c);
void monitor_write_colored(char *c, u8int backColour, u8int foreColour);
void monitor_display_clock_colored(u8int* currentTime, u8int backColour, u8int foreColour);

#endif
