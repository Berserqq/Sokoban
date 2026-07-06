#include <stdio.h>
#include <stdlib.h>
#include "../include/render.h"
#include "../include/game.h"
#include "../include/input.h"

void render_level(Game *game){
    // printf("\e[1;1H\e[2J"); //clear/cls

    system("clear");
    printf("\033[1;1H"); //cursor to the top-left corner

    for(int y = 0; y < game->level.height; y++){
        for(int x = 0; x < game->level.width; x++){
            putchar(game->level.cells[y][x]);
        }
        putchar('\n');
    }

    printf("\n");
    printf("WASD - move\n");
    printf("F - last move\n");
    printf("^C - quit\n");
}