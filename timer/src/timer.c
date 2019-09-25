/*
 * timer.c
 *
 *  Created on: 22 sep. 2019
 *      Author: exo
 */
#include "headers/timer.h"
#include <stdio.h>
#include <PR_Relays.h>

#define ON 1
#define OFF 0

#define MOTOR_BASE 1

typedef struct s_timer_handler_t{
	uint32_t time;
	Timer_Closure handler;
}timer_handler_t;

uint8_t flag = 0;

/**
 * Prendo los bits del timer 0 y apago los de los timers 1/2/3
 */
void power_up() {
	PCONP |= (1 << 1);
	PCONP &= ~(1 << 2);
}

/**
 * Segun tabla 42. Peripheral Clock Selection register bit values
 * 00 PCLK_peripheral = CCLK/4 00
 */
void select_clock_speed() {
	PCLKSEL_0 &= ~(3 << 2);
	T_PR = PRESCALE_FOR_1_US;
}

void close_timer() {
	T_TCR &= ~(1);	   // Apago  el temporizador,poniendo un cero en el bit 0 Pag 494
}

void open_timer(uint32_t time) {
	T_MR0 = time;
	T_TCR |= 1<<1;    //  Resteo el temporizador , prendiendo el bit 1
	T_TCR &= ~(1 << 1);// Apago el bit 1 de RESET
	T_TCR |= 1;        // Enciendo el temporizador poniendo el bit 0 de ENABLE en 1
}

void prepare_interrupts() {
	T_MCR |= 3;				// Genera una interrupcion cuando MC0 Matchea,  Resetea el TC cuando MC0 Matchea
	ISE_TIMER; 	// Habilito interrupcion del Timer0 en el vector de interrupciones.
}

void init_timer(void) {
	power_up();
	select_clock_speed();
	prepare_interrupts();
	close_timer();
}

timer_handler_t timer_handler;

void set_timer(uint32_t time,Timer_Closure handler) {
	timer_handler.time = time;
	timer_handler.handler = handler;
	open_timer(timer_handler.time);
}

void TIMER0_IRQHandler(void) {
	if(T_IR_MR0) {	 // Interrumpio por match 0 ?
		T_IR |= 0x01;
		close_timer();
		timer_handler.handler();
	}
}

