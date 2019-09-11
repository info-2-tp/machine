/**
 	\file KitInfo2FW_LCD.c
 	\brief Drivers del LCD
 	\details Validas para LCD de 4 bits de direccionamiento
 	\author Ing. Marcelo Trujillo
 	\date 2012.04.25
*/
#include "../Headers/KitInfo2.h"

extern volatile unsigned char Buffer_LCD[];
extern volatile unsigned int inxInLCD;
extern volatile unsigned int inxOutLCD;
extern volatile unsigned int cantidadColaLCD;
extern volatile int Demora_LCD;

void Inic_LCD( void )
{
	P05_PINSEL = GPIO;	FIO0DIR5 = SALIDA;	// d4
	P010_PINSEL = GPIO;	FIO0DIR10 = SALIDA;	// d5
	P24_PINSEL = GPIO;	FIO2DIR4 = SALIDA; 	// d6
	P25_PINSEL = GPIO;	FIO2DIR5 = SALIDA; 	// d7
	P26_PINSEL = GPIO;	FIO2DIR6 = SALIDA; 	// RS
	P128_PINSEL = GPIO;	FIO1DIR28 = ENTRADA;// BF
	P04_PINSEL = GPIO;	FIO0DIR4 = SALIDA;	// E


	Config_LCD( );
}

void Config_LCD( void )
{
	unsigned int i;

	LCD_E = OFF;
	Demora_LCD = 10;			// Demora inicial
	while (Demora_LCD);

	for( i = 0 ; i < 3 ; i++ )
	{
		LCD_d4 = 1;				// Configuracion en 8 bits
		LCD_d5 = 1;
		LCD_d6 = 0;
		LCD_d7 = 0;

		LCD_RS = OFF;
		LCD_E = ON;
		LCD_E = OFF;
		Demora_LCD = 2;
		while (Demora_LCD);
	}

	// Configuracion en 4 bits
	LCD_d4 = 0;
	LCD_d5 = 1;
	LCD_d6 = 0;
	LCD_d7 = 0;

	LCD_RS = OFF;
	LCD_E = ON;
	LCD_E = OFF;

	Demora_LCD = 1;	// Demora inicial
	while (Demora_LCD);

	// A partir de aca el LCD pasa a 4 bits !!!
	PushLCD( 0x28 , LCD_CONTROL );	// DL = 0: 4 bits de datos
									// N = 1 : 2 lineas
									// F = 0 : 5x7 puntos

	PushLCD( 0x08 , LCD_CONTROL);	// D = 0 : display OFF
									// C = 0 : Cursor OFF
									// B = 0 : Blink OFF

	PushLCD( 0x01 , LCD_CONTROL);	// clear display

	PushLCD( 0x06 , LCD_CONTROL);	// I/D = 1 : Incrementa puntero
									// S = 0 : NO Shift Display

	// Activo el LCD y listo para usar !
	PushLCD( 0x0C , LCD_CONTROL);	// D = 1 : display ON
									// C = 0 : Cursor OFF
									// B = 0 : Blink OFF
}

unsigned char PushLCD ( unsigned char dato , unsigned char control )
{
	if (cantidadColaLCD >= TOPE_BUFFER_LCD )
		return -1;

	Buffer_LCD [ inxInLCD ] = ( dato >> 4 ) & 0x0f;
	if ( control == LCD_CONTROL )
		Buffer_LCD [ inxInLCD ] |= 0x80;

	inxInLCD ++;
	inxInLCD %= TOPE_BUFFER_LCD;

	Buffer_LCD [ inxInLCD ] = dato & 0x0f;
	if ( control == LCD_CONTROL )
		Buffer_LCD [ inxInLCD ] |= 0x80;

	cantidadColaLCD += 2;

	inxInLCD ++;
	inxInLCD %= TOPE_BUFFER_LCD;

	return 0;
}

int PopLCD ( void )
{
	char dato;

	if ( cantidadColaLCD == 0 )
		return -1;

	dato = Buffer_LCD [ inxOutLCD ] ;

	cantidadColaLCD --;

	inxOutLCD ++;
	inxOutLCD %= TOPE_BUFFER_LCD;

	return dato;
}

void Dato_LCD(void)
{
	int data;

	if ( (data = PopLCD ()) == -1 )
		return;

	LCD_d7 = ((unsigned char ) data ) >> 3 & 0x01 ;
	LCD_d6 = ((unsigned char ) data ) >> 2 & 0x01 ;
	LCD_d5 = ((unsigned char ) data ) >> 1 & 0x01 ;
	LCD_d4 = ((unsigned char ) data ) >> 0 & 0x01 ;

	if( ((unsigned char ) data ) & 0x80 )
		LCD_RS = OFF ;	//Comando
	else
		LCD_RS = ON ;	//Dato

	LCD_E = ON ;LCD_E = OFF;
}
