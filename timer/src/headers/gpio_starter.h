/*
 * gpio_starter.h
 *
 *  Created on: 18 oct. 2019
 *      Author: exo
 */

#ifndef HEADERS_GPIO_STARTER_H_
#define HEADERS_GPIO_STARTER_H_

#include <DR_tipos.h>

#define		RELAY1				2,0
#define		RELAY2				0,23
#define		RELAY3				0,21
#define		RELAY4				0,27

#define     SW1                 2,10
#define     SW4                 0,18
#define     SW7                 0,11
#define     SW10                2,13
#define     SW13                1,26

#define		LED6				0,19
#define		LED1				1,29
#define		LED8				1,25
#define		IN0					1,22
#define		IN1					1,19

void init_gpio(void);

#endif /* HEADERS_GPIO_STARTER_H_ */
