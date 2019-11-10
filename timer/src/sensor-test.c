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
#include "headers/PR_HC_SR04.h"
#include "headers/gpio_starter.h"
#include <DR_gpio.h>

void init_cycle();

void init_cycle() {
	distance_t distance_in_cm = getDistance(MM);
	printf("Distancia: %dmm\n", distance_in_cm);
	startTimer(1, init_cycle, SECONDS);
}

int main(void) {
	initTimer();
	init_gpio();
	init_hc_sr04_sensor();

    printf("Hola Mundo!!\n");


    startTimer(1, init_cycle, SECONDS);

    while(1);

    return 0 ;
}
