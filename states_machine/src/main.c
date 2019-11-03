/**
*	\file main.c
*	\brief Resumen del contenido del archivo
*	\details Descripcion detallada del archivo
*	\author
*	\date 03-11-2019 01:34:46
*/
#include "./inc/states.h"

#define ALLWAYS 1
int current_state = INIT;

void main() {
    while(ALLWAYS) {
        state_machine();
    }
}
