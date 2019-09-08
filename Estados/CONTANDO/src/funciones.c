/**
*	\file funciones.c
*	\brief
*	\details Descripcion detallada del archivo
*	\author EduardoMaticorena
*	\date 24-08-2019 17:07:26
*/



extern int estado ;

#include "funciones.h"


void (*arrayFunciones[])(void) = {funcion_iniciar,funcion_cargar,funcion_contar,funcion_enviar};
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
	Relays(SENSOR, modo);
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
	Relays(SENSOR,OFF);//sensor
	Relays(MOTOR_BASE,OFF);//motor base
	Relays(MOTOR_TORRE,OFF);//motor torre
	Relays(MOTOR_CUCHILLA,OFF);//motor cuchilla
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
	Relays(MOTOR_BASE,ON);//motor base
	Relays(MOTOR_TORRE,ON);//motor torre
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
	Relays(MOTOR_BASE,modo);
}

void motorTorre(int modo)
{
	Relays(MOTOR_TORRE,modo);
}
char boton_ok (void){
	char orden;
	if(GetKey() == PULSADOR_INICIAR){
		orden=TRUE;
	}
	else{
		orden=FALSE;
	}
	return orden;
}

//funciones para la maquina

//comienzo


void funcion_iniciar (void)
{
	LCD_Display("R2D2",FIRST_LINE, 0);
	LCD_Display("Estado: INICIAR",SECOND_LINE, 0);

	if(pulsadorFinVuelta() && pulsadorFinTecho() )
	{
		detenerRelaysAll();
		LCD_Display("Calibrado",SECOND_LINE, 0);
		estado = CARGAR ;


	}

	if(!pulsadorFinTecho() && !pulsadorFinVuelta() )
	{
		LCD_Display("Calibrando...",SECOND_LINE, 0);

		motorBase(ON);
		motorTorre(ON);

		 estado = INICIAR ;

	}

}

void funcion_cargar(void){
	LCD_Display("Estado: CARGAR",FIRST_LINE, 0);
	LCD_Display("CARGUE CUBOS",SECOND_LINE, 0);

	if(boton_ok()== TRUE){
		estado = CONTAR ;
		motorBase(ON);
		sensorDistancia(ON);
	}
	else{
		detenerRelaysAll();
	}


}
void funcion_contar (void)
{
		LCD_Display("Estado: CONTAR",FIRST_LINE, 0);
		LCD_Display("contando...",SECOND_LINE, 0);


	if((pulsadorFinVuelta()==1 && pulsadorFinTecho() != 1) )
	{
		 estado = ENVIAR ;
		 detenerRelaysAll();
	}

	else{
		 estado = CONTAR ;
	}

}
void funcion_enviar (void)
{
		LCD_Display("Estado: ENVIAR",FIRST_LINE, 0);
		LCD_Display("Enviando... 10",SECOND_LINE, 0);

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
