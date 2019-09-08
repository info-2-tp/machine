/**
*	\file funciones.h
*	\brief Resumen del archivo
*	\details Descripcion detallada del archivo
*	\author EduardoMaticorena
*	\date 24-08-2019 17:07:26
*/

//headers

#include <DR_Infotronic.h>
#include <PR_Entradas.h>
#include <PR_lcd.h>
#include <PR_Relays.h>
#include <PR_Teclado.h>

//Declaracion de constantes
#define TRUE  1
#define FALSE  0
#define ON 1
#define OFF 0
#define PULSADOR_INICIAR 0x03
#define SENSOR 0
#define MOTOR_BASE 1
#define MOTOR_TORRE 2
#define MOTOR_CUCHILLA 3

#define ENTRADA0 0
#define ENTRADA1 1
//para el lcd
#define FIRST_LINE 0
#define SECOND_LINE 1
//declaracion de la maquina
void maquina_estado(void);


//Declaracion de estados
#define 	INICIAR	0
#define     CARGAR	1
#define 	CONTAR	2
#define 	ENVIAR	3

//Prototipos de las acciones
int pulsadorFinTecho(void);
int pulsadorFinVuelta(void);
void sensorDistancia(int modo);
void detenerRelaysAll(void);
void inicioConteoBloques(void);
void motorBase(int modo);
void motorTorre(int modo);
char boton_ok (void);


//estados
void funcion_iniciar (void);
void funcion_cargar(void);
void funcion_contar (void);
void funcion_enviar (void);
