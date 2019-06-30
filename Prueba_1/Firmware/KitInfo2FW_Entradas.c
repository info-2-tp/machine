/**
 	\file KitInfo2FW_Entradas.c
 	\brief Driver entradas digitales
 	\details Placa base
 	\author Ing. Marcelo Trujillo
 	\date 2012.04.25
*/

#include "../Headers/KitInfo2.h"

extern volatile unsigned char BufferEntradas;				//!< Buffer de Entradas Digitales

/**
	\fn void Debounce(void)
	\brief Filtrado de entradas digitales
 	\param void
	\return void
*/
void Debounce(void)
{
	unsigned char cambios,j = 0;

	static char ContadorEstados[ 4 ];

	j = in1;
	if ( in2 )
		j |= 0x02;

	cambios = ( BufferEntradas ^ j );

	if( cambios )
	{
		for( j = 0 ; j < ENTRADAS ; j++ )
		{
			if( cambios & (0x01 << j) )
			{
				ContadorEstados[ j ] ++;

				if(ContadorEstados[ j ] == ACEPTAReSTADO)
				{
					ContadorEstados[ j ] = 0;
					BufferEntradas = BufferEntradas ^ (0x01 << j);
				}
			}
			else
				ContadorEstados[ j ] = 0;
		}
	}
	else
	{
		for( j = 0 ; j < ENTRADAS ; j++ )
			ContadorEstados[ j ] = 0;
	}
}
