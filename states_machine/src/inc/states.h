//
// Created by marcelo on 2/11/19.
//

#ifndef STATES_MACHINE_STATES_H
#define STATES_MACHINE_STATES_H

#define     INIT    0
#define 	PREPARE	1
#define 	LOAD	2
#define 	STOP	3
#define 	MEASURING	4
#define 	OBI_WAN_COM	5
#define 	PREPARE_CUT	6
#define 	PREPARE_SNIFE	7
#define 	CUTTING	8
#define 	CUT_RETURNING	9
/**
*	\fn void state_machine()
*	\brief Resumen
*	\details Detalles
*	\author
*	\date 03-11-2019 01:34:46
*/
void state_machine();

void init_state();
void prepare_state();
void load_state();
void stop_state();
void measuring_state();

#endif //STATES_MACHINE_STATES_H
