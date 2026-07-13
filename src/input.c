/**
 * @file input.c
 * @brief 
 */

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "../include/input.h"
#include "../include/game.h"

int player_input(void){
    int key = getchar();

    switch (key)
    {
        case 'w':
            return KEY_UP;
        case 's':
            return KEY_DOWN;  
        case 'a':
            return KEY_LEFT;  
        case 'd':
            return KEY_RIGHT;
        case 'q':
            return KEY_ESCAPE;
        case '\r':
        case '\n':
            return KEY_ENTER;
        case 'f':
            return KEY_LAST_MOVE;
    }
}
//chat
static struct termios old_termios;

void input_init(void){
    struct termios new_termios;

    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;

    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void input_shutdown(void){
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}
//chat