#ifndef INPUT_H
#define INPUT_H
#include <stdio.h>

typedef enum{
    DIRECTION_UP = 1,
    DIRECTION_LEFT = 2,
    DIRECTION_DOWN = 3,
    DIRECTION_RIGHT = 4
} Direction;

int player_input(void);
#endif