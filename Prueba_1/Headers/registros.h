/* Author: Ing. Marcelo Trujillo */

#include "../Headers/lpc_types.h"						//!< Contiene a uint32_t, uint16_t y uint8_t

//Registros del CLOCK y de sistema:
//0x400FC0C4UL : Direccion de inicio del registro de habilitación de dispositivos:
#define 	DIR_PCONP	( ( uint32_t  * ) 0x400FC0C4UL )
#define		PCLKSEL		( ( uint32_t  * ) 0x400FC1A8UL )
//0x400FC1A0UL: Registro de control de sistema y registro de status:
#define	DIR_SCS	( (uint32_t *) 0x400FC1A0UL)
//0x400FC104UL: Registro de configuracion del clock:
#define	DIR_CCLKCFG	( (uint32_t *) 0x400FC104UL)
//0x400FC10CUL: Registro de seleccion del clock:
#define	DIR_CLKSRCSEL	( (uint32_t *) 0x400FC10CUL)
//0x400FC1C8UL: Clock Output Config register:
#define	DIR_CLKOUTCFG	( (uint32_t *) 0x400FC1C8UL)
//0x400FC000UL: Flash access configuration:
#define	DIR_FLASHCFG	( (uint32_t *) 0x400FC000UL)

//Registros de los PLL:
//0x400FC080UL: Registro de control del PLL0:
#define	DIR_PLL0CON	( (uint32_t *) 0x400FC080UL)
//0x400FC084UL: Registro de configuracion del PLL0:
#define	DIR_PLL0CFG	( (uint32_t *) 0x400FC084UL)
//0x400FC088UL: Registro de estado del PLL0:
#define	DIR_PLL0STAT	( (uint32_t *) 0x400FC088UL)
//0x400FC08CUL: Registro de control del PLL0:
#define	DIR_PLL0FEED	( (uint32_t *) 0x400FC08CUL)
//0x400FC0A0UL: Registro de control del PLL1:
#define	DIR_PLL1CON	( (uint32_t *) 0x400FC0A0UL)
//0x400FC0A4UL: Registro de configuracion del PLL1:
#define	DIR_PLL1CFG	( (uint32_t *) 0x400FC0A4UL)
//0x400FC0A8UL: Registro de estado del PLL1:
#define	DIR_PLL1STAT	( (uint32_t *) 0x400FC0A8UL)
//0x400FC0ACUL: Registro de control del PLL1:
#define	DIR_PLL1FEED	( (uint32_t *) 0x400FC0ACUL)



#define     __R     volatile const          /*!< defines 'read only' permissions      */
#define     __W     volatile                /*!< defines 'write only' permissions     */
#define     __RW	volatile                /*!< defines 'read / write' permissions   */

typedef union
{
	__RW uint32_t dword;
	__R  uint32_t dWord;
	struct
	{
		__RW uint16_t wordL;
		__RW uint16_t wordH;
	};

	struct
	{
		__RW uint8_t  byte0;
		__RW uint8_t  byte1;
		__RW uint8_t  byte2;
		__RW uint8_t  byte3;
	};
	
	struct
	{
		__R uint8_t  byte0;
		__R uint8_t  byte1;
		__R uint8_t  byte2;
		__R uint8_t  byte3;
	}r;
	
	struct
	{
		__W uint8_t  byte0;
		__W uint8_t  byte1;
		__W uint8_t  byte2;
		__W uint8_t  byte3;
	}w;
	
	struct
	{
		__RW uint32_t	bit00:1;
		__RW uint32_t	bit01:1;
		__RW uint32_t	bit02:1;
		__RW uint32_t	bit03:1;
		__RW uint32_t	bit04:1;
		__RW uint32_t	bit05:1;
		__RW uint32_t	bit06:1;
		__RW uint32_t	bit07:1;
		__RW uint32_t	bit08:1;
		__RW uint32_t	bit09:1;
		__RW uint32_t	bit10:1;
		__RW uint32_t	bit11:1;
		__RW uint32_t	bit12:1;
		__RW uint32_t	bit13:1;
		__RW uint32_t	bit14:1;
		__RW uint32_t	bit15:1;
		__RW uint32_t	bit16:1;
		__RW uint32_t	bit17:1;
		__RW uint32_t	bit18:1;
		__RW uint32_t	bit19:1;
		__RW uint32_t	bit20:1;
		__RW uint32_t	bit21:1;
		__RW uint32_t	bit22:1;
		__RW uint32_t	bit23:1;
		__RW uint32_t	bit24:1;
		__RW uint32_t	bit25:1;
		__RW uint32_t	bit26:1;
		__RW uint32_t	bit27:1;
		__RW uint32_t	bit28:1;
		__RW uint32_t	bit29:1;
		__RW uint32_t	bit30:1;
		__RW uint32_t	bit31:1;
	};

	struct
	{
		__R uint32_t	bit00:1;
		__R uint32_t	bit01:1;
		__R uint32_t	bit02:1;
		__R uint32_t	bit03:1;
		__R uint32_t	bit04:1;
		__R uint32_t	bit05:1;
		__R uint32_t	bit06:1;
		__R uint32_t	bit07:1;
		__R uint32_t	bit08:1;
		__R uint32_t	bit09:1;
		__R uint32_t	bit10:1;
		__R uint32_t	bit11:1;
		__R uint32_t	bit12:1;
		__R uint32_t	bit13:1;
		__R uint32_t	bit14:1;
		__R uint32_t	bit15:1;
		__R uint32_t	bit16:1;
		__R uint32_t	bit17:1;
		__R uint32_t	bit18:1;
		__R uint32_t	bit19:1;
		__R uint32_t	bit20:1;
		__R uint32_t	bit21:1;
		__R uint32_t	bit22:1;
		__R uint32_t	bit23:1;
		__R uint32_t	bit24:1;
		__R uint32_t	bit25:1;
		__R uint32_t	bit26:1;
		__R uint32_t	bit27:1;
		__R uint32_t	bit28:1;
		__R uint32_t	bit29:1;
		__R uint32_t	bit30:1;
		__R uint32_t	bit31:1;
	}R;

	struct
	{
		__RW uint32_t	bits0y1:2;
		__RW uint32_t	bits2y3:2;
		__RW uint32_t	bits4y5:2;
		__RW uint32_t	bits6y7:2;
		__RW uint32_t	bits8y9:2;
		__RW uint32_t	bits10y11:2;
		__RW uint32_t	bits12y13:2;
		__RW uint32_t	bits14y15:2;
		__RW uint32_t	bits16y17:2;
		__RW uint32_t	bits18y19:2;
		__RW uint32_t	bits20y21:2;
		__RW uint32_t	bits22y23:2;
		__RW uint32_t	bits24y25:2;
		__RW uint32_t	bits26y27:2;
		__RW uint32_t	bits28y29:2;
		__RW uint32_t	bits30y31:2;
	};

	// Estructuras para el ADC
	struct
	{
		__RW uint32_t	bits0a7:8;
		__RW uint32_t	bits8a15:8;
		__RW uint32_t	bits16:1;
		__RW uint32_t	bits17a20:4;
		__RW uint32_t	bits21:1;
		__RW uint32_t	bits22a23:2;
		__RW uint32_t	bits24a26:3;
		__RW uint32_t	bits27:1;
		__RW uint32_t	bits28a31:4;
	};

	struct
	{
		__RW uint32_t	bits0a3:4;
		__RW uint32_t	bits4a15:12;
		__RW uint32_t	bits16a23:8;
		__RW uint32_t	bits24a26:3;
		__RW uint32_t	bits27a29:3;
		__RW uint32_t	bits30:1;
		__RW uint32_t	bits31:1;
	}ADC2;

	struct
	{
		__RW uint32_t	bits0a3:4;
		__RW uint32_t	bits4a7:4;
		__RW uint32_t	bits8a11:4;
	}ADC3;

}register_t;

#define SYSTEMCORECLOCK		100000000UL	// 100 MHZ
//Registro PCONP:
#define		PCONP		DIR_PCONP[0]

//Registros PCLKSEL
#define		PCLKSEL0	PCLKSEL[0]
#define		PCLKSEL1	PCLKSEL[1]

#define	SCS			DIR_SCS[0]
#define FLASHCFG	DIR_FLASHCFG[0]

//Registros de control del CLOCK:
#define	CCLKCFG		DIR_CCLKCFG[0]
#define	CLKSRCSEL	DIR_CLKSRCSEL[0]
#define	CLKOUTCFG	DIR_CLKOUTCFG[0]

//PLL0:
#define	PLL0CON		DIR_PLL0CON[0]
#define	PLL0CFG		DIR_PLL0CFG[0]
#define	PLL0STAT	DIR_PLL0STAT[0]
#define	PLL0FEED	DIR_PLL0FEED[0]

//PLL1:
#define	PLL1CON		DIR_PLL1CON[0]
#define	PLL1CFG		DIR_PLL1CFG[0]
#define	PLL1STAT	DIR_PLL1STAT[0]
#define	PLL1FEED	DIR_PLL1FEED[0]

