/**
*	\file funciones.c
*	\brief
*	\details Descripcion detallada del archivo
*	\author EduardoMaticorena
*	\date 24-08-2019 17:07:26
*/



extern int estado ;

#include "funciones.h"
#include <DR_Infotronic.h>
#include <PR_Entradas.h>
#include <PR_lcd.h>
#include <PR_Relays.h>
#include <PR_Teclado.h>


void (*arrayFunciones[])(void) = {funcion_iniciar,funcion_contar,funcion_enviar};
//Funciones asociadas a los eventos

/**
*	\fn int pulsador_fin_techo(void)
*	\brief Resumen
*	\details Detalles
*	\author EduardoMaticorena
*	\date 24-08-2019 17:07:26
*/
int pulsadorFinTecho(void)
{
	return LeerEntrada(ENTRADA0);

}
int pulsadorFinVuelta(void)
{
	return LeerEntrada(ENTRADA1);

}

//Funciones asociadas a las acciones

/**
*	\fn void sensorDistancia(void)
*	\brief Resumen
*	\details Detalles
*	\author EduardoMaticorena
*	\date 24-08-2019 17:07:26
*/
void sensorDistancia(int modo)
{
	if(modo==ON){
		Relays(RELAY0,ON);
	}
	else{
		Relays(RELAY0,OFF);
	}
}

/**
*	\fn void detenerRelaysAll(void)
*	\brief Resumen
*	\details Detalles
*	\author EduardoMaticorena
*	\date 24-08-2019 17:07:26
*/
void detenerRelaysAll(void)
{
	Relays(RELAY0,OFF);//sensor
	Relays(RELAY1,OFF);//motor base
	Relays(RELAY2,OFF);//motor torre
	Relays(RELAY3,OFF);//motor cuchilla
}

/**
*	\fn void inicioConteoBloques(void)
*	\brief Resumen
*	\details Detalles
*	\author EduardoMaticorena
*	\date 24-08-2019 17:07:26
*/
void inicioConteoBloques(void)
{
	//imprimir que empiezo
	//empiezo a mover la base
	//empiezo a mover la torre
	Relays(RELAY1,ON);//motor base
	Relays(RELAY2,ON);//motor torre
}

/**
*	\fn void motorBase(void)
*	\brief Resumen
*	\details Detalles
*	\author EduardoMaticorena
*	\date 24-08-2019 17:07:26
*/
void motorBase(int modo)
{
	if(modo==ON){
		Relays(RELAY1,ON);
	}
	else{
		Relays(RELAY1,OFF);
	}
}
void motorTorre(int modo)
{
	if(modo==ON){
		Relays(RELAY2,ON);
	}
	else{
		Relays(RELAY2,OFF);
	}
}

//funciones para la maquina

//comienzo


void funcion_iniciar (void)
{

		LCD_Display("R2D2",LINE_0, 0);
		LCD_Display("Estado: INICIAR",LINE_1, 0);

	if((pulsadorFinVuelta()==1) && (pulsadorFinTecho()==1) )
	{
		motorBase(OFF);
		motorTorre(OFF);
		LCD_Display("Calibrado",LINE_1, 0);
		estado = CONTAR ;
		//motorBase(ON);
		sensorDistancia(ON);
	}

	if((pulsadorFinTecho()==0) && (pulsadorFinVuelta()==0) )
	{
			LCD_Display("Calibrando...",LINE_1, 0);

		motorBase(ON);
		motorTorre(ON);

		 estado = INICIAR ;

	}

}
void funcion_contar (void)
{
		LCD_Display("Estado: CONTAR",LINE_0, 0);
		LCD_Display("contando...",LINE_1, 0);


	if((pulsadorFinVuelta()==1 && pulsadorFinTecho() != 1) )
	{
		 estado = ENVIAR ;
		 detenerRelaysAll();
	}

	if((pulsadorFinVuelta()==0) )
	{
		//sensorDistancia(ON);
		 estado = CONTAR ;

	}

}
void funcion_enviar (void)
{
		LCD_Display("Estado: ENVIAR",LINE_0, 0);
		LCD_Display("Enviando... 10",LINE_1, 0);

	if( pulsadorFinTecho() == 1  )
	{
		 estado = INICIAR ;
		 inicioConteoBloques();
	}

}


//Maquina de estado mediante vector de ptr a funcion

/**
*	\fn void maquina_estado()
*	\brief Resumen
*	\details Detalles
*	\author EduardoMaticorena
*	\date 24-08-2019 17:07:26
*/
void maquina_estado()
{

	if(estado > ENVIAR )
	{

		estado = INICIAR;
		return;
	}

	(*arrayFunciones[estado])();
}
