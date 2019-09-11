/**
 	\file KitInfo2.h
 	\brief Configuracion de Infotronic
 	\author Ing. Marcelo Trujillo
 	\date 2012.04.25
*/

#ifndef KITINFO2_H_
	#define KITINFO2_H_
#endif
/** -------------------------------------------------------------------------------------
 * Archivos de cabecera
 */
#include "../Headers/Info2_cortexM3gpio.h"
#include "../Headers/Info2_cortexM3config.h"
#include "../Headers/Info2_CortexM3Systick.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** -------------------------------------------------------------------------------------
 * Macros de uso general
 */
#define	ON		1
#define	OFF		0
#define	SALIDA	1
#define	ENTRADA	0
#define	GPIO	0

/** -------------------------------------------------------------------------------------
 *Salidas
 */
#define		BEEPER		FIO0PIN28		//!< Beeper

#define		relay0		FIO0PIN23		//!< Relays
#define		relay1		FIO0PIN21
#define		relay2		FIO2PIN0
#define		relay3		FIO0PIN27

#define		RELAY0		0				//!< Numero de relay
#define		RELAY1		1
#define		RELAY2		2
#define		RELAY3		3

#define		led0		FIO2PIN1		//!< led
#define		led1		FIO2PIN2
#define		led2		FIO2PIN3

#define		LED0		0				//!< Numero de led
#define		LED1		1
#define		LED2		2

/** -------------------------------------------------------------------------------------
 *Entradas
 */
#define		in1				FIO4PIN29
#define		in2				FIO2PIN11

#define		Entrada0		(   BufferEntradas        & 0x01 )
#define		Entrada1		( ( BufferEntradas >> 1 ) & 0x01 )

#define		ACEPTAReSTADO	4
#define		ENTRADAS		2

/** -------------------------------------------------------------------------------------
 *Teclado
 */
#define		REBOTES		4

#define		fila0		FIO2PIN13
#define		fila1		FIO0PIN18
#define		fila2		FIO2PIN10
#define		fila3		FIO0PIN11

#define		F0			0
#define		F1			1
#define		F2			2
#define		F3			3
#define		F4			4
#define		F5			5
#define		F6			6
#define		F7			7

#define		NO_KEY		0xff

/** -------------------------------------------------------------------------------------
 *Temporizadores
 */
typedef	unsigned char		EVENTOS ;
typedef	unsigned char		TIEMPOS ;

#define		TIMERS			10				//!< Cantidad de temporizadores

#define		E_00			0
#define		E_01			1
#define		E_02			2

#define		T_00			2
#define		T_01			2
#define		T_02			2

#define		DECIMAS			50
#define		SEGUNDOS		10
#define		MINUTOS			60

/** -------------------------------------------------------------------------------------
 *PLACA EXPANSION 3
 */
//!< Display
#define		EX3_BCDA		FIO2PIN7
#define		EX3_BCDB		FIO1PIN29
#define		EX3_BCDC		FIO4PIN28
#define		EX3_BCDD		FIO1PIN23
#define		EX3_dp			FIO1PIN20

#define		EX3_MRS			FIO3PIN26
#define		EX3_CLOCK		FIO0PIN19

//!< Teclado
#define		EX3_fila0		FIO1PIN25
#define		EX3_fila1		FIO1PIN22
#define		EX3_fila2		FIO1PIN19
#define		EX3_fila3		FIO0PIN20

#define		EX3_columna0	FIO3PIN25
#define		EX3_columna1	FIO1PIN27

#define		DIGITOS		6

#define		DSP0		0				//!< Display verde
#define		DSP1		1				//!< Display rojo

//Valores para configuracion del PLL:
#define CLOCK_SETUP_Value 	    1
#define SCS_Value				0x00000020
#define CLKSRCSEL_Value         0x00000001
#define PLL0_SETUP_Value        1
#define PLL0CFG_Value           0x00050063
#define PLL1_SETUP_Value        1
#define PLL1CFG_Value           0x00000023
#define CCLKCFG_Value           0x00000003
#define USBCLKCFG_Value         0x00000000
#define PCLKSEL0_Value          0x00000000
#define PCLKSEL1_Value          0x00000000
#define PCONP_Value             0x042887DE
#define CLKOUTCFG_Value         0x00000000
#define FLASHCFG_Value			0x00004000



//#define	_winstar1602a
#define _winstar1602b
#define 	RENGLON_1		0
#define 	RENGLON_2		1
#define 	TOPE_BUFFER_LCD		160


#ifdef _winstar1602a					//Agregado para el LCD Winstar WH1602A
	#define		LCD_d4			FIO2PIN4
	#define		LCD_d5			FIO2PIN5
	#define		LCD_d6			FIO0PIN5
	#define		LCD_d7			FIO0PIN10
	#define		LCD_RS			FIO0PIN4
	#define		LCD_BF			FIO1PIN28
	#define		LCD_E			FIO2PIN6
#else

#ifdef _winstar1602b
	#define		LCD_d4			FIO0PIN5
	#define		LCD_d5			FIO0PIN10
	#define		LCD_d6			FIO2PIN4
	#define		LCD_d7			FIO2PIN5
	#define		LCD_RS			FIO2PIN6
	#define		LCD_BF			FIO1PIN28
	#define		LCD_E			FIO0PIN4
#endif
#endif



#define		LCD_CONTROL		1
#define		LCD_DATA		0


/** -------------------------------------------------------------------------------------
 * Prototipos
 */
//!< KitInfo2FW_7Seg.c
void BarridoDisplay( void );

//!< KitInfo2PR_7Seg.c
void Display(int ,char );

//!< KitInfo2PR_gpio.c
void Led (char , char );
void Relays (char , char );

//!< KitInfo2FW_Teclado.c
void DriverTeclado( void );
void DriverTecladoSW ( unsigned char );
unsigned char DriverTecladoHW( void );

//!< KitInfo2PR_Teclado.c
unsigned char Teclado( void );

//!< KitInfo2FW_Entradas.c
void Debounce(void);

//!< KitInfo2FW_Inicializacion.c
void Inic_Teclado_BB( void );
void Inic_Relays( void );
void Inic_Entradas( void );
void Inic_Leds ( void );
void Inic_Expansion2( void );
void Inicializar( void );
void Inic_SysTick( void );
void InitPLL ( void );

//!< KitInfo2PR_Timer.c
void TimerStart(int , TIEMPOS );
void TimerStop(int );
void TimerEvent(void);
void AnalizarTimer( int );

//!< KitInfo2AP_Pruebas.c
void Base ( unsigned char ) ;
void EX3_Prueba ( unsigned char ) ;

//!< LCD
void Dato_LCD ( void );
void Display_lcd ( char * , char  , char  );
void Inic_LCD ( void );
unsigned char PushLCD ( unsigned char , unsigned char );
int PopLCD ( void );
void Config_LCD( void );

