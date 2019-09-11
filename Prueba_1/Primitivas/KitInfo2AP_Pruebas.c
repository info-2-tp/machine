/**
 	\file KitInfo2AP_Pruebas.c
 	\brief Aplicacion de prueba de funciones de Infotronic
 	\details Placa base + Expansion 2
 	\author Ing. Marcelo Trujillo
 	\date 2012.04.25
*/

#include "../Headers/KitInfo2.h"

// Buffer de Entradas
extern volatile unsigned char BufferEntradas;

/**
	\fn  void Base ( unsigned char c )
	\brief Prueba de la placa BASE
 	\param [in] c Tecla a analizar
	\return void
*/
void Base ( unsigned char c )
{
	static char fEntrada0 , fEntrada1 ;

	TimerEvent();

	switch ( c )
	{
		case F0:
			Relays ( RELAY0 , ON ) ;
			Relays ( RELAY1 , OFF ) ;
			Relays ( RELAY2 , OFF ) ;
			Relays ( RELAY3 , OFF ) ;
			BEEPER = ON ;
			break;
		case F1:
			Relays ( RELAY0 , OFF ) ;
			Relays ( RELAY1 , ON ) ;
			Relays ( RELAY2 , OFF ) ;
			Relays ( RELAY3 , OFF ) ;
			BEEPER = OFF ;
			break;
		case F2:
			Relays ( RELAY0 , OFF ) ;
			Relays ( RELAY1 , OFF ) ;
			Relays ( RELAY2 , ON ) ;
			Relays ( RELAY3 , OFF ) ;
			BEEPER = ON ;
			break;
		case F3:
			Relays ( RELAY0 , OFF ) ;
			Relays ( RELAY1 , OFF ) ;
			Relays ( RELAY2 , OFF ) ;
			Relays ( RELAY3 , ON ) ;
			BEEPER = OFF ;
			break;
	}

	if ( Entrada0 == 0 && fEntrada0 == 0 )
	{
		Display (1,DSP1);
		fEntrada0 = 1 ;
	}

	if ( Entrada0 == 1 && fEntrada0 == 1 )
	{
		Display (0,DSP1);
		fEntrada0 = 0 ;
	}

	if ( Entrada1 == 0 && fEntrada1 == 0 )
	{
		Display (2,DSP1);

		fEntrada1 = 1 ;
	}

	if ( Entrada1 == 1 && fEntrada1 == 1 )
	{
		Display (0,DSP1);

		fEntrada1 = 0 ;
	}
}

/**
	\fn   EX3_Prueba ( unsigned char c )
	\brief Prueba de la placa Expansion 2
 	\param [in] c Tecla a analizar
	\return void
*/
void EX3_Prueba ( unsigned char c )
{
	static char PrimeraVez = 0;

	if ( !PrimeraVez )
	{
		Display(123,DSP0);
		Display(456,DSP1);
		PrimeraVez = 1;

	}

	if ( c != NO_KEY )
		Display(c,DSP0);
}

