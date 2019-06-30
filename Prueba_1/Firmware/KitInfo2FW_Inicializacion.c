/**
 	\file KitInfo2FW_Inicializacion.c
 	\brief Driver Configuracion del HW e inicializacion de la aplicacion
 	\details Placa base + Expansion 2
 	\author Ing. Marcelo Trujillo
 	\date 2012.04.25
*/

#include "../Headers/KitInfo2.h"

/**
	\fn void Debounce(void)
	\brief Inicializacion de HW y aplicacion
 	\param void
	\return void
*/
void Inicializar( void )
{
	P028_PINSEL = GPIO;	FIO0DIR28 = SALIDA; //Buzzer
	BEEPER = ON;
	BEEPER = OFF;
	BEEPER = ON;
	Inic_Leds ( );
	Inic_Teclado_BB( );
	Inic_Relays( );
	Inic_Entradas( );
	Inic_Expansion2( );
	InitPLL( );
    Inic_SysTick( );
    TimerStart( E_01 , T_01 );
    BEEPER = ON;
	Display(12,DSP0);
	Display(345,DSP1);
	Inic_LCD( ) ;

}

/**
	\fn void Inic_Teclado_BB( void )
	\brief Inicializacion del teclado de la placa base
 	\param void
	\return void
*/
void Inic_Teclado_BB( void )
{
	P213_PINSEL = GPIO;	FIO2DIR13 = ENTRADA;
	P018_PINSEL = GPIO;	FIO0DIR18 = ENTRADA;
	P210_PINSEL = GPIO;	FIO2DIR10 = ENTRADA;
	P011_PINSEL = GPIO;	FIO0DIR11 = ENTRADA;
}

/**
	\fn void Inic_Relays( void )
	\brief Inicializacion de las salidas de relay y beeper de la placa base
 	\param void
	\return void
*/
void Inic_Relays( void )
{
	P023_PINSEL = GPIO;	FIO0DIR23 = SALIDA;
	P021_PINSEL = GPIO;	FIO0DIR21 = SALIDA;
	P20_PINSEL = GPIO;	FIO2DIR0 = SALIDA;
	P027_PINSEL = GPIO;	FIO0DIR27 = SALIDA;

	P028_PINSEL = GPIO;	FIO0DIR28 = SALIDA;
}

/**
	\fn void Inic_Entradas( void )
	\brief Inicializacion de las entradas digitales de la placa base
 	\param void
	\return void
*/
void Inic_Entradas( void )
{
	P429_PINSEL = GPIO;	FIO4DIR29 = ENTRADA;
	P211_PINSEL = GPIO;	FIO2DIR11 = ENTRADA;
}

/**
	\fn void Inic_Leds ( void )
	\brief Inicializacion del led RGB
 	\param void
	\return void
*/
void Inic_Leds ( void )
{
	// Configuracion de los leds
	P21_PINSEL = GPIO;	FIO2DIR1 = SALIDA;
	P22_PINSEL = GPIO;	FIO2DIR2 = SALIDA;
	P23_PINSEL = GPIO;	FIO2DIR3 = SALIDA;
}

/**
	\fn void Inic_SysTick( void ))
	\brief Inicializacion del System Tick
 	\param void
	\return void
*/
void Inic_SysTick( void )
{
	STRELOAD  = ( STCALIB/5) - 1 ;     //* set reload register

	STCURR = 0;                        //* Load the SysTick Counter Value

	//* Enable SysTick IRQ and SysTick Timer
	ENABLE = 1;
	TICKINT = 1;
	CLKSOURCE = 1;

	return ;
}

/**
	\fn void Inic_Expansion2( void )
	\brief Inicializacion de la Expansion 2
 	\param void
	\return void
*/
void Inic_Expansion2( void )
{
	//!< BCD
	P123_PINSEL = GPIO;	FIO1DIR23 = SALIDA; //!< Expansion 3 - BCDD
	P428_PINSEL = GPIO;	FIO4DIR28 = SALIDA; //!< Expansion 2 - BCDC
	P129_PINSEL = GPIO;	FIO1DIR29 = SALIDA; //!< Expansion 1 - BCDB
	P27_PINSEL = GPIO;	FIO2DIR7 = SALIDA; 	//!< Expansion 0 - BCDA

	//!< dp
	P120_PINSEL = GPIO;	FIO1DIR20 = SALIDA; //!< Expansion 4

	//!< Teclado
	P125_PINSEL = GPIO;	FIO1DIR25 = ENTRADA; //!< Expansion 7
	P122_PINSEL = GPIO;	FIO1DIR22 = ENTRADA; //!< Expansion 8
	P119_PINSEL = GPIO;	FIO1DIR19 = ENTRADA; //!< Expansion 9
	P020_PINSEL = GPIO;	FIO0DIR20 = ENTRADA; //!< Expansion 10

	P325_PINSEL = GPIO;	FIO3DIR25 = SALIDA;  //!< Expansion 11
	P127_PINSEL = GPIO;	FIO1DIR27 = SALIDA;  //!< Expansion 12

	//!< Control
	P019_PINSEL = GPIO;	FIO0DIR19 = SALIDA; //!< Expansion 5 - CLK
	P326_PINSEL = GPIO;	FIO3DIR26 = SALIDA; //!< Expansion 6 - RST
}
void InitPLL ( void )
{

	//Este bloque de codigo habilita el oscilador externo como fuente de clk
	//del micro, y configura un dispositivo conocido como PLL (Phase Locked Loop)
	//para generar un clock interno de 100MHz a partir del oscilador conectado

	SCS = SCS_Value;

	if (SCS_Value & (1 << 5))               /* If Main Oscillator is enabled      */
		while ((SCS & (1<<6)) == 0);/* Wait for Oscillator to be ready    */

	CCLKCFG   = CCLKCFG_Value;      /* Setup Clock Divider                */

	PCLKSEL0  = PCLKSEL0_Value;     /* Peripheral Clock Selection         */
	PCLKSEL1  = PCLKSEL1_Value;

	CLKSRCSEL = CLKSRCSEL_Value;    /* Select Clock Source for PLL0       */

	PLL0CFG   = PLL0CFG_Value;      /* configure PLL0                     */
	PLL0FEED  = 0xAA;
	PLL0FEED  = 0x55;

	PLL0CON   = 0x01;             /* PLL0 Enable                        */
	PLL0FEED  = 0xAA;
	PLL0FEED  = 0x55;

	while (!(PLL0STAT & (1<<26)));/* Wait for PLOCK0                    */

	PLL0CON   = 0x03;             /* PLL0 Enable & Connect              */
	PLL0FEED  = 0xAA;
	PLL0FEED  = 0x55;

	while (!(PLL0STAT & ((1<<25) | (1<<24))));/* Wait for PLLC0_STAT & PLLE0_STAT */

	PLL1CFG   = PLL1CFG_Value;
	PLL1FEED  = 0xAA;
	PLL1FEED  = 0x55;

	PLL1CON   = 0x01;             /* PLL1 Enable                        */
	PLL1FEED  = 0xAA;
	PLL1FEED  = 0x55;

	while (!(PLL1STAT & (1<<10)));/* Wait for PLOCK1                    */

	PLL1CON   = 0x03;             /* PLL1 Enable & Connect              */
	PLL1FEED  = 0xAA;
	PLL1FEED  = 0x55;

	while (!(PLL1STAT & ((1<< 9) | (1<< 8))));/* Wait for PLLC1_STAT & PLLE1_STAT */

	PCONP     = PCONP_Value;        /* Power Control for Peripherals      */

	CLKOUTCFG = CLKOUTCFG_Value;    /* Clock Output Configuration         */

	FLASHCFG  = (FLASHCFG & ~0x0000F000) | FLASHCFG_Value;
}

