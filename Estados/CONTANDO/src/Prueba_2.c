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

//void (*arrayFunciones[])(void) = {funcion_iniciar,funcion_contar,funcion_enviar};

int main(void) {
	Inicializacion();
	Display(0,1);
	while(1)
		{

			maquina_estado();

		}
	return 0 ;
}
