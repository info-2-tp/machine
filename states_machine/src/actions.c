//
// Created by marcelo on 2/11/19.
//
#include <stdio.h>

void knifes_stop() {
    printf("Parar cuchillas\n");
}
void move_knife_tower_up() {
    printf("Mover torre hacia arriba\n");
};
void knife_tower_stop() {
    printf("Parar torre\n");
};

void move_base_bottom() {
    printf("Mover base hacia el inicio\n");
};

void move_base_middle() {
    printf("Mover base hacia el medio\n");
};

void base_stop() {
    printf("Parar Base\n");
};

void stop_all() {
    knifes_stop();
    base_stop();
    knife_tower_stop();
};