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

#define ON 1
#define OFF 0

#define MOTOR_BASE 1

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void) {

	Inicializacion();
	//InicializarRGB( );

    printf("Hola mundo\n");

    Relays(MOTOR_BASE,ON);

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        i++ ;
    }
    return 0 ;
}
