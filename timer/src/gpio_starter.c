/*
 * gpio_starter.c
 *
 *  Created on: 18 oct. 2019
 *      Author: exo
 */
#include "headers/gpio_starter.h"
#include <DR_pinsel.h>
#include <DR_gpio.h>

void init_gpio() {
	SetPINSEL(RELAY1,FUNCION_GPIO);
	SetPINSEL(RELAY2,FUNCION_GPIO);
	SetPINSEL(RELAY3,FUNCION_GPIO);
	SetPINSEL(RELAY4,FUNCION_GPIO);

	SetDIR( RELAY1 , SALIDA);
	SetDIR( RELAY2 , SALIDA);
	SetDIR( RELAY3 , SALIDA);
	SetDIR( RELAY4 , SALIDA);

	SetPIN(RELAY1,OFF);
	SetPIN(RELAY2,OFF);
	SetPIN(RELAY3,OFF);
	SetPIN(RELAY4,OFF);
}


