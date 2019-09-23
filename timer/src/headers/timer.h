#ifndef TIMER_DRIVER_V0_1_0_H_
#define TIMER_DRIVER_V0_1_0_H_

#include <DR_tipos.h>

// Registro de control de poder de perifericos
#define 	PCONP	(* ( ( __RW uint32_t  * ) 0x400FC0C4UL ))

// Seleccion de la velocidad de clock, los bit 2:3 son para el timer 0
// Son el el registro PCLKSEL0
#define		PCLKSEL0_P		( ( __RW uint32_t  * ) 0x400FC1A8UL )
#define		PCLKSEL_0		PCLKSEL0_P[0]

//Estructura para manejar el timer
typedef struct
{
	uint32_t	IR;
	uint32_t	TCR;
	uint32_t 	TC;
	uint32_t 	PR;
	uint32_t 	PC;
	uint32_t 	MCR;
	uint32_t	MR0;
	uint32_t	MR1;
	uint32_t	MR2;
	uint32_t	MR3;
	uint32_t	CCR;
	uint32_t	CR0;
	uint32_t	CR1;       // 0x40004030 para el T0
	uint32_t    RESERVE[2];// 0x40004034 para el T0
						   // 0x40004038 para el T0
	uint32_t    EMR;       // 0x4000403C para el T0

} timer_t;

//0x40004000UL : Direccion de inicio de los registros del Timer0
#define	DIR_TIMER	( ( timer_t  * ) 0x40004000UL )
#define	TIMER	DIR_TIMER[0]

// Timer 0
#define		T_IR		TIMER.IR
#define     T_IR_MR0   T_IR & 0X01       // Bit 0 del registro IR corresponde al flag de la Int por Match 0
#define     T_IR_MR1   (T_IR & (0X01 <<1))>>1 // Bit 1 del registro IR corresponde al flag de la Int por Match 1
#define     T_IR_MR2   (T_IR & (0X01 <<2))>>2 // Bit 2 del registro IR corresponde al flag de la Int por Match 2
#define     T_IR_MR3   (T_IR & (0X01 <<3))>>3 // Bit 3 del registro IR corresponde al flag de la Int por Match 3
#define     T_IR_CR0   (T_IR & (0X01 <<1))>>4 // Bit 4 del registro IR corresponde al flag de la Int por CAPTURE 0
#define     T_IR_CR1   (T_IR & (0X01 <<1))>>5 // Bit 5 del registro IR corresponde al flag de la Int por CAPTURE 1

#define		T_TCR		TIMER.TCR
#define		T_PC		TIMER.PC
#define		T_PR		TIMER.PR
#define		T_MCR		TIMER.MCR
#define		T_MR0		TIMER.MR0
#define		T_MR1		TIMER.MR1
#define		T_MR2		TIMER.MR2
#define		T_MR3		TIMER.MR3
#define		T_CCR		TIMER.CCR
#define		T_CR0		TIMER.CR0
#define		T_CR1		TIMER.CR1
#define		T_EMR		TIMER.EMR

//0xE000E100UL : Direccion de inicio de los registros de habilitación (set) de interrupciones en el NVIC:
#define		ISER		( ( uint32_t * ) 0xE000E100UL )
//0xE000E180UL : Direccion de inicio de los registros de deshabilitacion (clear) de interrupciones en el NVIC:
#define		ICER		( (  uint32_t * ) 0xE000E180UL )

#define     ISE_TIMER  ISER[0] |= (0x00000001)<<  1   //ISER0->bit1 pongo un 1 en el bit 1 para habilitar la INT TIMER0

#define PRESCALE_FOR_1_US 25	//Prescaler puesto a 25 para que el clock sea de a 1 microsegundo

void init_timer(void);

#endif //TIMER_DRIVER_V0_1_0_H_
