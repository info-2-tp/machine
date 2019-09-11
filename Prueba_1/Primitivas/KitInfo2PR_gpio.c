/**
 	\file KitInfo2PR_7Seg.c
 	\brief Primitiva de Didplsy de 7 segmentos
 	\details Valida para Expansion 2 y Expansion 3
 	\author Ing. Marcelo Trujillo
 	\date 2012.04.25
*/

#include "../Headers/KitInfo2.h"

extern unsigned char BufferLeds;							//!< Variable de estado de las LEDS
extern volatile unsigned char BufferSalidas;				//!< Buffer de Salidas Relay

/**
	\fn  void Led (char n, char estado)
	\brief tratamiento de los leds
 	\param [in] n numero de led
 	\param [in] estado al que se lo quiere llevar (o : OFF, 1 : ON)
	\return void
*/
void Led (char n, char estado)
{
	if ( estado )
		BufferLeds |= (1 << n);
	else
   		BufferLeds &= (~(1 << n));
}

/**
	\fn  void Relays (char n, char estado)
	\brief Tratamiento der los relays
 	\param [in] n numero de relay
 	\param [in] estado al que se lo quiere llevar (o : OFF, 1 : ON)
	\return void
*/
void Relays (char n, char estado)
{
	if ( estado )
		BufferSalidas |= (1 << n);
	else
		BufferSalidas &= (~(1 << n));
}
