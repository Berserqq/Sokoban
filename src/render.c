#include <stdio.h>
#include <stdlib.h>

#include "../include/render.h"
#include "../include/game.h"


void render_level(Game *game){
    char info[2][16];
    snprintf(info[0], sizeof(info[1]), "   Moves: %d", game->moves);
    snprintf(info[1], sizeof(info[2]), "   Boxes: %d/%d", crates_on_targets(game), game->level.total_crates);

    printf("\033[2J");
    printf("\033[H");

    printf("%s", game->level.name);
    for (int y = 0; y < game->level.height; y++)
    {
        for (int x = 0; x < game->level.width; x++){
            switch (game->level.cells[y][x])
            {
                case '@': printf(ANSI_ORANGE "@" ANSI_RESET); break;
                case '$': printf(ANSI_YELLOW "$" ANSI_RESET); break;
                case 'x': printf(ANSI_RED "x" ANSI_RESET); break;
                case 'O': printf(ANSI_GREEN "O" ANSI_RESET); break;
                default: putchar(game->level.cells[y][x]);
            }
        }
            
        if(y < 2){
            printf("%s", info[y]);
        }
        putchar('\n');
    }

    printf("\n");
    printf("WASD - Move\n");
    printf("F    - Undo\n");
    printf("Q    - Back\n");
}