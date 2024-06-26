#ifndef CLOCK_H
#define CLOCK_H

#include "common.h"
#include "isr.h"
#include "monitor.h"

void init_clock();
void set_time(u8int hour, u8int minute, u8int second);
void write_time();

#endif // CLOCK_H