/**
 	\file KitInfo2FW_Teclado.c
 	\brief Driver Driver de teclado
 	\details Placa base
 	\author Ing. Marcelo Trujillo
 	\date 2012.04.25
*/

#include "../Headers/KitInfo2.h"

extern volatile unsigned char key;	//!< Buffer de teclado

/**
	\fn void DriverTeclado(void)
	\brief Driver de teclado
 	\param void
	\return void
*/
void DriverTeclado(void)
{
	unsigned char CodigoActual ;

	CodigoActual = DriverTecladoHW( );
	DriverTecladoSW( CodigoActual );
}

/**
	\fn  void DriverTecladoSW ( unsigned char CodigoActual )
	\brief filtrado del rebote de tecla
 	\param [in] c codigo de tecla a analizar
	\return void
*/
void DriverTecladoSW ( unsigned char CodigoActual )
{
	static unsigned char CodigoAnterior = NO_KEY;
	static unsigned char EstadosEstables;

	if( CodigoActual == NO_KEY )
	{
		CodigoAnterior = NO_KEY;
		EstadosEstables = 0;
		return;
	}

	if( EstadosEstables == 0  )
	{
		CodigoAnterior = CodigoActual;
		EstadosEstables = 1;
		return;
	}

	if( CodigoActual != CodigoAnterior )
	{
		CodigoAnterior = NO_KEY;
		EstadosEstables = 0;
		return;
	}

	if( EstadosEstables == REBOTES )
	{
		key = CodigoActual;
		EstadosEstables++;

		return;
	}

	if( EstadosEstables == REBOTES + 1)
		return;

	EstadosEstables ++;

	return;
}

/**
	\fn unsigned char DriverTecladoHW( void )
	\brief lectura de los microswitch del teclado
 	\param void
	\return el codigo de tecla leido
*/
unsigned char DriverTecladoHW( void )
{
	unsigned char Codigo = NO_KEY;

	EX3_columna0 = OFF ;
	EX3_columna1 = ON ;
	EX3_columna1 = ON ;
	EX3_columna1 = ON ;
	EX3_columna1 = ON ;
	EX3_columna1 = ON ;
	EX3_columna1 = ON ;
	EX3_columna1 = ON ;
	EX3_columna1 = ON ;
	EX3_columna1 = ON ;
	EX3_columna1 = ON ;

	if ( !EX3_fila0 )
		return 0 ;

	if ( !EX3_fila1 )
		return 1 ;

	if ( !EX3_fila2 )
		return 2 ;

	if ( !EX3_fila3 )
		return 3 ;

	EX3_columna0 = ON ;
	EX3_columna1 = OFF ;
	EX3_columna1 = OFF ;
	EX3_columna1 = OFF ;
	EX3_columna1 = OFF ;
	EX3_columna1 = OFF ;
	EX3_columna1 = OFF ;
	EX3_columna1 = OFF ;
	EX3_columna1 = OFF ;
	EX3_columna1 = OFF ;
	EX3_columna1 = OFF ;

	if ( !EX3_fila0 )
		return 4 ;

	if ( !EX3_fila1 )
		return 5 ;

	if ( !EX3_fila2 )
		return 6 ;

	if ( !EX3_fila3 )
		return 7 ;

	return Codigo ;
}
