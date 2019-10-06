/*
 * PR_timer.c
 *
 *  Created on: 6 oct. 2019
 *      Author: exo
 */

#include "headers/PR_timer.h"
#include "headers/DR_timer.h"

#define MICROSECOND 1
#define MILLISECOND 1000
#define SECOND 1000*1000

#define TIMERS_MAX_SIZE 256

#define CLOSED 1
#define OPENED 0

typedef struct pr_timer{
	uint32_t time;
	Timer_Closure handler;
	uint8_t base;
	uint8_t closed;
}pr_timer_t;

pr_timer_t timers[TIMERS_MAX_SIZE];
uint8_t current_descriptor = 0;

uint32_t base_to_microseconds(uint8_t base) {
	switch(base) {
		case 'u': return MICROSECOND;
		case 'm': return MILLISECOND;
		case 's': return SECOND;
	};
	return MICROSECOND;
}

uint32_t timer_in_microseconds(uint32_t time, uint8_t base) {
	return time*base_to_microseconds(base);
}

void initTimer() {
	init_timer();
}

uint8_t startTimer(uint32_t time, Timer_Closure handler , uint8_t base ) {
    pr_timer_t timer = timers[current_descriptor];
	timer.time = time;
    timer.handler = handler;
    timer.base = base;
    timer.closed = OPENED;
    set_timer_from_now(timer_in_microseconds(timer.time, timer.base), handler);
    return current_descriptor++;
}
