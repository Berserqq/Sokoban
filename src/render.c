#include <stdio.h>
#include <stdlib.h>

#include "../include/render.h"
#include "../include/game.h"
#include "../include/input.h"
#include "../include/menu.h"

void render_level(Game *game, Counters *counters)
{
    char info[3][64];

    snprintf(info[0], sizeof(info[0]), "   %s", game->level.name);
    snprintf(info[1], sizeof(info[1]), "   Moves: %d", counters->moves);
    snprintf(info[2], sizeof(info[2]), "   Boxes: %d/%d", placed_boxes(game), max_score(game));

    system("clear");
    printf("\033[H");

    for (int y = 0; y < game->level.height; y++)
    {
        for (int x = 0; x < game->level.width; x++)
            putchar(game->level.cells[y][x]);

        if (y < 3)
            printf("%s", info[y]);

        putchar('\n');
    }

    printf("\n");
    printf("WASD - Move\n");
    printf("F    - Undo\n");
    printf("Q    - Back\n");
}