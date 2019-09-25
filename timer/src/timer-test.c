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
#include <PR_Relays.h>
#include "headers/timer.h"

#define ON 1
#define OFF 0

#define MOTOR_BASE 1

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

void close_motor() {
	Relays(MOTOR_BASE, OFF);
}

void open_motor() {
	Relays(MOTOR_BASE, ON);
	set_timer(3000000, close_motor);
}

int main(void) {

	Inicializacion();
	init_timer();

    printf("Hola mundo\n");
    set_timer(1000000, open_motor);

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        i++ ;
    }
    return 0 ;
}
