//
// Created by marcelo on 2/11/19.
//
//Maquina de estado mediante vector de ptr a funcion

#include "./inc/actions.h"
#include "./inc/events.h"
#include "./inc/states.h"

extern int current_state;

void (*state_functions[])() = {init_state};

void init_state() {
    knifes_stop();
    move_knifes_up();
    move_base_bottom();
    current_state = PREPARE;
    printf("ESTADO --> PREPARE\n");
}

void prepare_state() {
}

void state_machine() {
    state_functions[current_state]();
}
