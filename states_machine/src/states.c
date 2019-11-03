//
// Created by marcelo on 2/11/19.
//
//Maquina de estado mediante vector de ptr a funcion

#include "./inc/actions.h"
#include "./inc/events.h"
#include "./inc/states.h"
#include "./inc/PR_lcd.h"

//MOCK
void LCD_Display(const char *string, unsigned char line ,unsigned char pos) {
    printf(string);
}

extern int current_state;

void (*state_functions[])() = {init_state,prepare_state, load_state, stop_state, measuring_state};

void init_state() {
    knifes_stop();
    move_knife_tower_up();
    move_base_bottom();
    current_state = PREPARE;
    printf("ESTADO --> PREPARE\n");
}

void stop_state() {
    if ( run_button()) {
        knifes_stop();
        move_knife_tower_up();
        move_base_bottom();
        current_state = PREPARE;
        printf("ESTADO --> PREPARE\n");
    }
}

void prepare_state() {
    if (stop_button()) {
        stop_all();
        current_state = STOP;
        printf("ESTADO --> STOP\n");
        return;
    }

    if ( base_bottom() ){
        base_stop();
    }

    if (knifes_top()) {
        knife_tower_stop();
    }

    if (base_bottom() && knifes_top()) {
        LCD_Display("Ya se pueden cargar cubos\n", 0, 0);
        current_state = LOAD;
        printf("ESTADO --> LOAD\n");
    }
}

void load_state() {
    if (stop_button()) {
        stop_all();
        current_state = STOP;
        printf("ESTADO --> STOP\n");
        return;
    }

    if ( run_button()) {
        move_base_middle();
        current_state = MEASURING;
        printf("ESTADO --> MEASURING\n");
    }
}

void measuring_state() {
    if (stop_button()) {
        stop_all();
        current_state = STOP;
        printf("ESTADO --> STOP\n");
        return;
    }

    //TODO
}

void state_machine() {
    state_functions[current_state]();
}
