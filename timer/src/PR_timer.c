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

#define MAX = (uint32_t)0xffffff

#define TIMERS_MAX_SIZE 10

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
uint32_t last_time = 0;
uint8_t next_timer_descriptor = 0;

void empty_handler() {}

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

void init_timer_buffer() {
	for (uint8_t i = 0; i < TIMERS_MAX_SIZE; i++){
		pr_timer timer = timers[i];
		timer.time = 0;
		timer.handler = empty_handler;
		timer.base = MICROSECONDS;
		timer.closed = CLOSED;
	}
}

void initTimer() {
	init_timer_buffer();
	init_timer();
}

pr_timer initialize_timer(uint8_t descriptor, uint32_t time, Timer_Handler handler , uint8_t base) {
	pr_timer_t timer = timers[descriptor];
	timer.time = timer_in_microseconds(time, base);
	timer.handler = handler;
	timer.base = base;
	timer.closed = OPENED;
	return timer;
}

uint8_t modify_timers(uint32_t current_time, uint32_t last_time) {
	uint32_t time = current_time - last_time;
	uint32_t min_timer = MAX;
	uint8_t min_index = 0;
	for (uint8_t i = 0; i < TIMERS_MAX_SIZE; i++) {
		pr_timer_t timer = timers[i];
		if (!timer.closed) {
			timer.time-= time;
			if (timer.time < min_timer) {
				min_timer = timer.time;
				min_index = i;
			}
		}
	}
	return min_index;
}

uint8_t organize_timers() {
	uint32_t current_time = get_clock();
	uint8_t next_index = modify_timers(current_time, last_time);
	last_time = current_time;
	return next_index;
}

void activate_next_timer(uint8_t next_descriptor, pr_timer_t timer) {
	next_timer_descriptor = descriptor;
	set_timer_from_now(timer_in_microseconds(timer.time), timer.handler);
}

uint8_t startTimer(uint32_t time, Timer_Handler handler , uint8_t base ) {
	uint8_t next_index = organize_timers();
	pr_timer_t timer = initialize_timer(current_descriptor, time, handler, base);
	if (timer.time < timers[next_index].time || timers[next_index].closed)
		activate_next_timer(current_descriptor, timer);
	else
		activate_next_timer(next_index, timers[next_index]);
    uint8_t descriptor = current_descriptor;
    current_descriptoe = (current_descriptor + 1) % TIMERS_MAX_SIZE;
    return descriptor;
}
