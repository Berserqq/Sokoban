#include <stdio.h>
#include "../include/input.h"
#include "../include/game.h"

int player_input(void){
    char key = getchar();
        switch (key)
    {
        case 'w':
            return 1;
            break;
        case 'a':
            return 2;
            break;
        case 's':
            return 3;
            break;
        case 'd':
            return 4;
            break;
        case 'f':
            return 5;
            break;
    }
    
    return 0;
}