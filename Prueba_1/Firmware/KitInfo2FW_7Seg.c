/**
 	\file KitInfo2FW_7Seg.c
 	\brief Drivers del display de 7 segmentos
 	\details Expansion 2
 	\author Ing. Marcelo Trujillo
 	\date 2012.04.25
*/

#include "../Headers/KitInfo2.h"

extern volatile unsigned char Digitos[DIGITOS];			//!< Buffer de display

/**
	\fn void BarridoDisplay( void )
	\brief Barrido del display de 7 segmentos
 	\param void
	\return void
*/
void BarridoDisplay( void )
{
	unsigned char aux ;
	static int	digito = 0 ;

	EX3_BCDA = ON ;
	EX3_BCDB = ON ;
	EX3_BCDC = ON ;
	EX3_BCDD = ON ;
	EX3_dp = OFF;

	if( !digito )
	{
		EX3_MRS = ON;
		EX3_MRS = OFF;
	}
	else
	{
		EX3_CLOCK = OFF ;
		EX3_CLOCK = ON ;
	}
 	aux = Digitos[ digito ] ;

 	EX3_BCDA =   aux        & 0x01 ;
 	EX3_BCDB = ( aux >> 1 ) & 0x01 ;
 	EX3_BCDC = ( aux >> 2 ) & 0x01 ;
 	EX3_BCDD = ( aux >> 3 ) & 0x01 ;

	digito++ ;
	digito %= DIGITOS ;
}
