/*
===============================================================================
 Name        : timer-test.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>
#include "headers/DR_timer.h"
#include "headers/PR_timer.h"
#include "headers/DR_HC_SR04.h"
#include "headers/gpio_starter.h"
#include <DR_gpio.h>

uint8_t crono;

void init_cycle();

void init_cycle() {
	trigger_turn_on();
	wait(10);
	trigger_turn_off();
	while(!echo_on());
	uint8_t c = startCronometer();
	while(echo_on());
	uint32_t t = stopCronometer(c);
	printf("Tiempo: %d\n", t);
	startTimer(1000, init_cycle, MILLISECONDS);
}

int main(void) {
	initTimer();
	init_gpio();
	init_hc_sr04();

    printf("Hola Mundo!!\n");


    startTimer(1, init_cycle, SECONDS);

    while(1);

    return 0 ;
}
