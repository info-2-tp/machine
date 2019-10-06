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

void init_pLL () {
	//Este bloque de codigo habilita el oscilador externo como fuente de clk
	//del micro, y configura un dispositivo conocido como PLL (Phase Locked Loop)
	//para generar un clock interno de 100MHz a partir del oscilador conectado

	SCS       = SCS_Value;

	if (SCS_Value & (1 << 5))               /* If Main Oscillator is enabled      */
		while ((SCS & (1<<6)) == 0);/* Wait for Oscillator to be ready    */

	CCLKCFG   = CCLKCFG_Value;      /* Setup Clock Divider                */

	PCLKSEL0  = PCLKSEL0_Value;     /* Peripheral Clock Selection         */
	PCLKSEL1  = PCLKSEL1_Value;

	CLKSRCSEL = CLKSRCSEL_Value;    /* Select Clock Source for PLL0       */

	PLL0CFG   = PLL0CFG_Value;      /* configure PLL0                     */
	PLL0FEED  = 0xAA;
	PLL0FEED  = 0x55;

	PLL0CON   = 0x01;             /* PLL0 Enable                        */
	PLL0FEED  = 0xAA;
	PLL0FEED  = 0x55;

	while (!(PLL0STAT & (1<<26)));/* Wait for PLOCK0                    */

	PLL0CON   = 0x03;             /* PLL0 Enable & Connect              */
	PLL0FEED  = 0xAA;
	PLL0FEED  = 0x55;

	while (!(PLL0STAT & ((1<<25) | (1<<24))));/* Wait for PLLC0_STAT & PLLE0_STAT */

	PLL1CFG   = PLL1CFG_Value;
	PLL1FEED  = 0xAA;
	PLL1FEED  = 0x55;

	PLL1CON   = 0x01;             /* PLL1 Enable                        */
	PLL1FEED  = 0xAA;
	PLL1FEED  = 0x55;

	while (!(PLL1STAT & (1<<10)));/* Wait for PLOCK1                    */

	PLL1CON   = 0x03;             /* PLL1 Enable & Connect              */
	PLL1FEED  = 0xAA;
	PLL1FEED  = 0x55;

	while (!(PLL1STAT & ((1<< 9) | (1<< 8))));/* Wait for PLLC1_STAT & PLLE1_STAT */

	PCONP     = PCONP_Value;        /* Power Control for Peripherals      */

	CLKOUTCFG = CLKOUTCFG_Value;    /* Clock Output Configuration         */

	FLASHCFG  = (FLASHCFG & ~0x0000F000) | FLASHCFG_Value;
}

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

void open_timer() {
	T0_TCR |= 1;
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
	init_pLL();
	power_up();
	select_clock_speed();
	prepare_interrupts();
	start_timer();
	start_clock();
}

timer_handler_t timer_handler;

void set_timer(uint32_t time,Timer_Closure handler) {
	open_timer();
	timer_handler.time = time;
	timer_handler.handler = handler;
	T0_MR0 = time;
}

void set_timer_from_now(uint32_t time,Timer_Closure handler) {
	open_timer();
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
		close_timer();
		timer_handler.handler();
	}
}

