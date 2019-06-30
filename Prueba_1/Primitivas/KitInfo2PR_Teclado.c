/**
 	\file KitInfo2PR_Teclado.c
 	\brief Primitiva de teclado
 	\details Valida para BASE y Expansion 3 y Expansion 4
 	\author Ing. Marcelo Trujillo
 	\date 2012.04.25
*/
#include "../Headers/KitInfo2.h"

extern volatile unsigned char key;	//!< Buffer de teclado

/**
	\fn  unsigned char Teclado( void )
	\brief Lectura del buffer de teclado
 	\param void
	\return codigo de tecla si hay tecla en el buffer o NO_KEY si no la hay
*/
unsigned char Teclado( void )
{
	unsigned char Key = NO_KEY;

	TimerEvent( );

	if (key != NO_KEY )
	{
		Key = key;
		key = NO_KEY;
	}
	return Key;
}
