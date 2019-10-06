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

void step1() {
	printf("step 1, Pasaron %ius\n", get_clock());
}

void step3() {
	printf("step 3, Pasaron %ius\n", get_clock());
}

void step4() {
	printf("step 4, Pasaron %ius\n", get_clock());
}

void step2() {
	printf("step 2, Pasaron %ius\n", get_clock());
    startTimer(1, step3, SECONDS);
    startTimer(4, step4, SECONDS);
}

void step0() {
	printf("step 0, Pasaron %ius\n", get_clock());
    startTimer(5, step1, SECONDS);
    startTimer(2, step2, SECONDS);
}

int main(void) {

	initTimer();

    printf("Hola Mundo!!\n");

    startTimer(1, step0, SECONDS);
    printf("Pasaron %ius\n", get_clock());

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        i++ ;
    }
    return 0 ;
}
