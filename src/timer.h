#ifndef TIMER_H
#define TIMER_H

#include "common.h"

typedef struct periodic_timer {
    u32int period;
    int tick_count;
    u8int fired;
} periodic_timer_t;

void set_timer_periodic(periodic_timer_t *timer, u32int period);
void reset_timer(periodic_timer_t *timer);

void init_timer(u32int frequency);

extern u32int initial_esp;

#endif
