#ifndef INPUT_H
#define INPUT_H
#include <stdio.h>

typedef enum{
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_ENTER,
    KEY_ESCAPE,
    KEY_LAST_MOVE
} Input;

int player_input(void);
void input_init(void);
void input_shutdown(void);

#endif