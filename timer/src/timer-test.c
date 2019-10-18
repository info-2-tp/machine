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

uint32_t times[6];
uint8_t cron;
uint8_t cron2;
uint8_t cron3;

void step1() {
	times[1] = stopCronometerInBase(cron, MILLISECONDS);
}

void step3() {
	times[3] = stopCronometerInBase(cron2,MILLISECONDS);
}

void step5() {
	times[5] = stopCronometerInBase(cron, MICROSECONDS);
	printf("step\n0: %ims\n1: %ims\n2: %ims\n3: %ims\n4: %ims\n5: %ius\n", times[0], times[1], times[2], times[3], times[4], times[5]);
}

void step4() {
	times[4] = stopCronometerInBase(cron3, MILLISECONDS);
	cron = startCronometer();
    startTimer(10, step5, MICROSECONDS);
}

void step2() {
	times[2] = stopCronometerInBase(cron2, MILLISECONDS);
	cron2 = startCronometer();
    startTimer(1, step3, SECONDS);
    cron3 = startCronometer();
    startTimer(4, step4, SECONDS);
}

void step0() {
	times[0] = stopCronometerInBase(cron, MILLISECONDS);
	cron = startCronometer();
	startTimer(5, step1, SECONDS);
	cron2 = startCronometer();
    startTimer(2, step2, SECONDS);
}

int main(void) {

	initTimer();

    printf("Hola Mundo!!\n");

    cron = startCronometer();
    startTimer(1, step0, SECONDS);

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        i++ ;
    }
    return 0 ;
}
