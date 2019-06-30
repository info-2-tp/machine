/**
 	\file main.c
 	\brief Programa de prueba de funciones de Infotronic
 	\details Placa base + Expansion 3
 	\author Ing. Marcelo Trujillo
 	\date 2012.04.25
*/

#include "../Headers/KitInfo2.h"

volatile unsigned char Digitos[DIGITOS];			//!< Buffer de display
unsigned char BufferLeds;							//!< Variable de estado de las LEDS
volatile unsigned char key = NO_KEY;				//!< Buffer de teclado
volatile unsigned char BufferSalidas;				//!< Buffer de Salidas Relay
volatile unsigned char BufferEntradas;				//!< Buffer de Entradas Digitales
volatile TIEMPOS TmrRun[TIMERS] ;					//!< Buffer de Temporizadores
volatile EVENTOS Evento[TIMERS] ;					//!< Buffer de eventos vencidos
volatile unsigned char decimas = DECIMAS ;			//!< Base de tiempo decimas
volatile unsigned char segundos = SEGUNDOS ;		//!< Base de tiempo segundos
volatile uint8_t Buffer_LCD[TOPE_BUFFER_LCD];
volatile uint32_t inxInLCD;
volatile uint32_t inxOutLCD;
volatile uint32_t cantidadColaLCD;
volatile uint32_t Demora_LCD;


int main( void )
{
	unsigned char c;

	Inicializar( ) ;
	Display_lcd( "R2-D2:" , 0 , 0 );

	Display(000 ,0 );
	Display(000 ,1 );

	while(1)
	{
		c = Teclado( ) ;
		if(c ==F0){
			Display_lcd( "Calculando cubos" , 1 , 0 );
			Relays(RELAY0,ON);
		}
		else if(c==F1){
			Display_lcd( "***Terminado***" , 1 , 0 );
			Relays(RELAY0,OFF);
			Display(5 ,1 );
		}


	}
	return 0;
}
