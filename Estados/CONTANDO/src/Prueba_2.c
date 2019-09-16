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
#include "funciones.h"

// TODO: insert other definitions and declarations here
int estado = INICIAR;
char lectura = 1;
int esta_lcd = -1;

int main(void) {

	Inicializacion();

	while(1)
		{
			Display(2,0);
			maquina_estado();

		}
	return 0 ;
}
