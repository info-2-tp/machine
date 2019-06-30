/**
 	\file KitInfo2PR_LCD.c
 	\brief Primitiva del LCD
 	\details Validas para LCD de 2 lineas
 	\author Ing. Marcelo Trujillo
 	\date 2012.04.25
*/
#include "../Headers/KitInfo2.h"

extern volatile unsigned char Buffer_LCD[];


void Display_lcd( char * msg, char r , char p )
{
	unsigned char i ;

	switch ( r )
	{
		case RENGLON_1:
			PushLCD( p + 0x80 , LCD_CONTROL );
			break;
		case RENGLON_2:
			PushLCD( p + 0xc0 , LCD_CONTROL );
			break;
	}
	for( i = 0 ; msg[ i ] != '\0' ; i++ )
		PushLCD( msg [ i ] , LCD_DATA );
}
