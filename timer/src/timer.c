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

void prepare_interrupts() {
	T_MCR |= 3;				// Genera una interrupcion cuando MC0 Matchea,  Resetea el TC cuando MC0 Matchea
	T_TCR &= ~(1);	   // Apago  el temporizador,poniendo un cero en el bit 0 Pag 494
	T_TCR |= 1<<1;    //  Resteo el temporizador , prendiendo el bit 1

	T_TCR &= ~(1 << 1);// Apago el bit 1 de RESET
	T_TCR |= 1;        // Enciendo el temporizador poniendo el bit 0 de ENABLE en 1

	ISE_TIMER; 	// Habilito interrupcion del Timer0 en el vector de interrupciones.
}

void init_timer(void) {
	T_MR0 = 5000000;
	power_up();
	select_clock_speed();
	prepare_interrupts();
}

void TIMER0_IRQHandler(void) {
	if(T_IR_MR0) {	 // Interrumpio por match 0 ?
		T_IR |= 0x01;
		printf("Interrumpio jojo\n");
		flag = (flag+1)%2;
		Relays(MOTOR_BASE, flag);
	}
}

