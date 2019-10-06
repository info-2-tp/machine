/*
 * timer.c
 *
 *  Created on: 22 sep. 2019
 *      Author: exo
 */
#include <stdio.h>
#include <PR_Relays.h>

#include "headers/DR_timer_regs.h"
#include "headers/DR_timer.h"

typedef struct s_timer_handler_t{
	uint32_t time;
	Timer_Closure handler;
}timer_handler_t;

/**
 * Prendo los bits del timer 0 y apago los de los timers 1/2/3
 */
void power_up() {
	PCONP |= (1 << 1);
	PCONP |= (1 << 2);
}

/**
 * Segun tabla 42. Peripheral Clock Selection register bit values
 * 00 PCLK_peripheral = CCLK/4 00
 */
void select_clock_speed() {
	PCLKSEL_0 &= ~(3 << 2);
	PCLKSEL_0 &= ~(3 << 4);
	T0_PR = PRESCALE_FOR_1_US;
	T1_PR = PRESCALE_FOR_1_US;
}

void close_timer() {
	T0_TCR &= ~(1);	   // Apago  el temporizador,poniendo un cero en el bit 0 Pag 494
}

void prepare_interrupts() {
	T0_MCR |= 3;				// Genera una interrupcion cuando MC0 Matchea,  Resetea el TC cuando MC0 Matchea
	ISE_TIMER_0; 				// Habilito interrupcion del Timer0 en el vector de interrupciones.
}

void start_timer() {
	T0_TCR &= ~(1);	   // Apago  el temporizador,poniendo un cero en el bit 0 Pag 494
	T0_TCR |= 1<<1;    //  Resteo el temporizador , prendiendo el bit 1
	T0_TCR &= ~(1 << 1);// Apago el bit 1 de RESET
	T0_TCR |= 1;        // Enciendo el temporizador poniendo el bit 0 de ENABLE en 1
}

void start_clock() {
	T1_TCR &= ~(1);	   // Apago  el temporizador,poniendo un cero en el bit 0 Pag 494
	T1_TCR |= 1<<1;    //  Resteo el temporizador , prendiendo el bit 1
	T1_TCR &= ~(1 << 1);// Apago el bit 1 de RESET
	T1_TCR |= 1;        // Enciendo el temporizador poniendo el bit 0 de ENABLE en 1
}

void init_timer(void) {
	power_up();
	select_clock_speed();
	prepare_interrupts();
	start_timer();
	start_clock();
}

timer_handler_t timer_handler;

void set_timer(uint32_t time,Timer_Closure handler) {
	timer_handler.time = time;
	timer_handler.handler = handler;
	T0_MR0 = time;
}

void set_timer_from_now(uint32_t time,Timer_Closure handler) {
	timer_handler.time = get_timer_clock() + time;
	timer_handler.handler = handler;
	T0_MR0 = timer_handler.time;
}

uint32_t get_timer_clock() {
	return TC_0;
}

uint32_t get_clock() {
	return TC_1;
}

void TIMER0_IRQHandler(void) {
	if(T0_IR_MR0) {	 // Interrumpio por match 0 ?
		T0_IR |= 0x01;
		timer_handler.handler();
	}
}

