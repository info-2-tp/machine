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

void step1() {
	times[1] = get_clock();
}

void step3() {
	times[3] = get_clock();
}

void step5() {
	times[5] = get_clock();
	printf("step\n0: %ius\n1: %ius\n2: %ius\n3: %ius\n4: %ius\n5: %ius\n", times[0], times[1], times[2], times[3], times[4], times[5]);
}

void step4() {
	times[4] = get_clock();
    startTimer(10, step5, MICROSECONDS);
}

void step2() {
	times[2] = get_clock();
    startTimer(1, step3, SECONDS);
    startTimer(4, step4, SECONDS);
}

void step0() {
	times[0] = get_clock();
    startTimer(5, step1, SECONDS);
    startTimer(2, step2, SECONDS);
}

int main(void) {

	initTimer();

    printf("Hola Mundo!!\n");

    printf("Pasaron %ius\n", get_clock());

    startTimer(1, step0, SECONDS);

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        i++ ;
    }
    return 0 ;
}
