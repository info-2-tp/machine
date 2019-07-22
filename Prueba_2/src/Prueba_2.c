/*
===============================================================================
 Name        : Prueba_2.c
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
#include <DR_Infotronic.h>
#include <PR_Entradas.h>
#include <PR_lcd.h>
#include <PR_Relays.h>
#include <PR_Teclado.h>
#include <PR_7seg.h>
#define ENTRADA0 0
#define F0 0x03
#define RELAY0 0
#define LINE_0 0
#define LINE_1 1

// TODO: insert other include files here
unsigned int FinPrimeraVuelta(void);
// TODO: insert other definitions and declarations here

int main(void) {

	// TODO: insert code here

	// Force the counter to be placed into memory
	unsigned int cant =0;
	Inicializacion();
	Display(0,1);
	LCD_Display("R2D2:",LINE_0, 0);
	LCD_Display("Bienvenido!!!",LINE_1, 0);

	// Enter an infinite loop, just incrementing a counter
	while(1) {
		cant = FinPrimeraVuelta();
		Display(cant,0);
	}
	return 0 ;
}

unsigned int FinPrimeraVuelta(void){
	unsigned int cant= 5;
	uint8_t entrada=0,tecla=0;
	entrada = LeerEntrada(ENTRADA0);
	tecla =GetKey();
	if(tecla == F0){
		LCD_Display("Boton activado", LINE_0, 0);
		LCD_Display("Relay prendido",LINE_1, 0);
		Relays(RELAY0, ON);
		tecla = 0;
	}
	if(entrada == 1){
		LCD_Display("Entrada activa", LINE_0, 0);
		LCD_Display("Relay apagado", LINE_1, 0);
		Relays(RELAY0, OFF);
	}
	return cant;
}
