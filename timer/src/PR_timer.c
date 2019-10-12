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

#define MAX (uint32_t)0xffffff

#define TIMERS_MAX_SIZE 10
#define NO_NEXT TIMERS_MAX_SIZE + 1

#define CLOSED 1
#define OPENED 0

#define ZERO 0

typedef struct pr_timer{
	uint32_t time;
	Timer_Closure handler;
	uint8_t base;
	uint8_t closed;
	uint8_t next;
}pr_timer_t;

pr_timer_t timers[TIMERS_MAX_SIZE];
uint8_t current_descriptor = 0;
uint32_t last_time = 0;
uint8_t next_timer_descriptor = 0;
uint8_t next_timer = NO_NEXT;

void timer_handler_function(void);

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
		pr_timer_t* timer = timers + i;
		timer->time = 0;
		timer->handler = empty_handler;
		timer->base = MICROSECONDS;
		timer->closed = CLOSED;
	}
}

void initTimer() {
	init_timer_buffer();
	init_timer();
}

pr_timer_t initialize_timer(uint8_t descriptor, uint32_t time, Timer_Handler handler , uint8_t base) {
	pr_timer_t* timer = timers + descriptor;
	timer->time = timer_in_microseconds(time, base);
	timer->handler = handler;
	timer->base = base;
	timer->closed = OPENED;
	return *timer;
}

uint8_t modify_timers(uint32_t current_time, uint32_t last_time) {
	uint32_t time = current_time - last_time;
	uint32_t min_timer = MAX;
	uint8_t min_index = NO_NEXT;
	uint32_t second_timer = MAX;
	uint8_t second_index = NO_NEXT;
	for (uint8_t i = 0; i < TIMERS_MAX_SIZE; i++) {
		pr_timer_t* timer = timers + i;
		if (!timer->closed) {
			timer->time-= time;
			if (timer->time < min_timer) {
				second_timer = min_timer;
				second_index = min_index;
				min_timer = timer->time;
				min_index = i;
			} else if (timer->time < second_timer) {
				second_timer = timer->time;
				second_index = i;
			}
		}
	}
	timers[min_index].next = second_index;
	return min_index;
}

uint8_t organize_timers(uint32_t current_time) {
	uint8_t next_index = modify_timers(current_time, last_time);
	last_time = current_time;
	return next_index;
}

void activate_next_timer(uint8_t next_descriptor, uint32_t past_time) {
	next_timer_descriptor = next_descriptor;
	pr_timer_t timer = timers[next_descriptor];
	set_timer_from_now(timer.time - past_time, timer_handler_function);
}

uint8_t startTimer(uint32_t time, Timer_Handler handler , uint8_t base ) {
	uint32_t current_time = get_clock();
	uint32_t past_time = current_time - last_time;
	//uint8_t next_index = organize_timers(get_clock()); //Esto se puede poner abajo?
	pr_timer_t timer = initialize_timer(current_descriptor, time, handler, base);
	if (next_timer > TIMERS_MAX_SIZE || timer.time < timers[next_timer].time - past_time || timers[next_timer].closed)
		activate_next_timer(current_descriptor, ZERO);
	else
		activate_next_timer(next_timer, past_time);
	next_timer = organize_timers(current_time);
    uint8_t descriptor = current_descriptor;
    current_descriptor = (current_descriptor + 1) % TIMERS_MAX_SIZE;
    return descriptor;
}

void timer_handler_function() {
	uint32_t current_time = get_clock();
	uint32_t past_time = current_time - last_time;
	pr_timer_t* timer = timers + next_timer_descriptor;
	timer->closed = CLOSED;
	next_timer = timer->next;
	//	uint8_t next_index = organize_timers(last_time + timer->time);
	if (next_timer < TIMERS_MAX_SIZE) {
		activate_next_timer(next_timer, past_time);
	}
	timer->handler();
	organize_timers(current_time);
}
