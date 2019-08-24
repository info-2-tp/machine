/**
*	\file funciones.h
*	\brief Resumen del archivo
*	\details Descripcion detallada del archivo
*	\author EduardoMaticorena
*	\date 24-08-2019 17:07:26
*/

//Declaracion de constantes
#define TRUE  1
#define FALSE  0
#define ON 1
#define OFF 0
#define RELAY0 0//sensor
#define RELAY1 1//motor base
#define RELAY2 2//motor torre
#define RELAY3 3//motor cuchilla
#define ENTRADA0 0
#define ENTRADA1 1
//para el lcd
#define LINE_0 0
#define LINE_1 1
//declaracion de la maquina
void maquina_estado(void);


//Declaracion de estados
#define 	INICIAR	0
#define 	CONTAR	1
#define 	ENVIAR	2

//Prototipos de las acciones
int pulsadorFinTecho(void);
int pulsadorFinVuelta(void);
void sensorDistancia(int modo);
void detenerRelaysAll(void);
void inicioConteoBloques(void);
void motorBase(int modo);
void motorTorre(int modo);


//estados
void funcion_iniciar (void);
void funcion_contar (void);
void funcion_enviar (void);
