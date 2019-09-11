/**
 	\file KitInfo2PR_7Seg.c
 	\brief Primitiva de Didplsy de 7 segmentos
 	\details Valida para Expansion 2 y Expansion 3
 	\author Ing. Marcelo Trujillo
 	\date 2012.04.25
*/

#include "../Headers/KitInfo2.h"

extern volatile unsigned char Digitos[DIGITOS];			//!< Buffer de display

// Buffer de Salidas
extern volatile unsigned char BufferSalidas;

/**
	\fn  void Display(int Val,char dsp)
	\brief Presentacion de valores en el display
 	\param [in] val valor a mostrar
 	\param [in] dsp seleccion del sector del display
	\return void
*/
void Display(int Val,char dsp)
{
	unsigned char a ;
	char aux[4];


	aux[0] = aux[1] = aux[2] = aux[3] = 0;

	if( Val < 0 )
	{

        Val = -Val;
	}

	//* Convierto a 7 Seg.
	for(a = 2 ; a ; a-- )
	{
		aux[a] = Val % 10 ;
		Val /= 10;
	}
	aux[ 0 ] = Val ;

	switch(dsp)
	{
		case DSP0:
			Digitos[ 2 ] = aux[ 2 ];
			Digitos[ 1 ] = aux[ 1 ];
			Digitos[ 0 ] = aux[ 0 ];
			break;

		case DSP1:
			Digitos[ 5 ] = aux[ 2 ];
			Digitos[ 4 ] = aux[ 1 ];
			Digitos[ 3 ] = aux[ 0 ];
			break;
	}
}
