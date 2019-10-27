/*
 * DR_HC_SR04.c
 *
 *  Created on: 26 oct. 2019
 *      Author: exo
 */
#include "./headers/DR_HC_SR04.h"
#include <DR_pinsel.h>
#include <DR_gpio.h>

void init_hc_sr04() {
	SetPINSEL(TRIGGER, FUNCION_GPIO);
	SetPINSEL(ECHO, FUNCION_GPIO);

	SetDIR( TRIGGER, SALIDA);
	SetDIR( ECHO, ENTRADA);

	SetMODE(ECHO, NONE);

	SetPIN(TRIGGER, OFF);
}

void trigger_turn_on() {
	SetPIN(TRIGGER, ON);
}

void trigger_turn_off() {
	SetPIN(TRIGGER, OFF);
}

uint8_t echo_off() {
	return !GetPIN(ECHO, ALTO);
}

uint8_t echo_on() {
	return GetPIN(ECHO, ALTO);
}


