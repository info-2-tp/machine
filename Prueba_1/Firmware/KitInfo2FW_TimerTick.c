/**
 	\file KitInfo2FW_TimerTick.c
 	\brief Interrupcion del System Tick
 	\details Placa base
 	\author Ing. Marcelo Trujillo
 	\date 2012.04.25
*/

#include "../Headers/KitInfo2.h"

extern unsigned char BufferLeds;							//!< Variable de estado de las LEDS
extern volatile unsigned char BufferSalidas;				//!< Buffer de Salidas Relay
extern volatile unsigned char decimas;						//!< Base de tiempo decimas
extern volatile unsigned char segundos;						//!< Base de tiempo segundos
extern volatile uint8_t Buffer_LCD[];
extern volatile uint32_t inxInLCD;
extern volatile uint32_t inxOutLCD;
extern volatile uint32_t cantidadColaLCD;
extern volatile uint32_t Demora_LCD;
/**
	\fn  void SysTick_Handler(void)
	\brief handler de la interrupcion del systick
 	\param void
	\return void
*/
void SysTick_Handler(void)
{
	DriverTeclado( );
	Debounce( );
	BarridoDisplay( );
	Dato_LCD( );

	relay0 =   BufferSalidas        & 0x01;
	relay1 = ( BufferSalidas >> 1 ) & 0x01;
	relay2 = ( BufferSalidas >> 2 ) & 0x01;
	relay3 = ( BufferSalidas >> 3 ) & 0x01;

	led0 =   BufferLeds        & 0x01;
	led1 = ( BufferLeds >> 1 ) & 0x01;
	led2 = ( BufferLeds >> 2 ) & 0x01;

	decimas-- ;

	if ( Demora_LCD )
		Demora_LCD--;

 	if( !decimas ) // Decimas ------------------------------------------------------------------
	{
		decimas = DECIMAS ;

		segundos-- ;

		AnalizarTimer( E_00 ) ;
		AnalizarTimer( E_01 ) ;
		AnalizarTimer( E_02 ) ;

		if( !segundos )
		{
			segundos = SEGUNDOS ;
		}
	}
}
