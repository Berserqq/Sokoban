/**
 * @file render.c
 * @brief Реализация отрисовки игрового уровня и вывода статистики.
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/render.h"
#include "../include/game.h"



void render_level(Game *game){
    char info[2][16];
    //Запись статистики в соответствующие поля
    snprintf(info[0], sizeof(info[0]), "   Moves: %d", game->moves);
    snprintf(info[1], sizeof(info[1]), "   Boxes: %d/%d", crates_on_targets(game), game->level.total_crates);

    system("clear");
    
    //Вывод названия уровня в первую строку терминала
    printf("%s", game->level.name);
    //Вывод уровня
    for (int y = 0; y < game->level.height; y++)
    {
        for (int x = 0; x < game->level.width; x++){
            //Вывод символа и его цвета
            switch (game->level.cells[y][x])
            {
                case '@': printf( "%s@" ANSI_RESET, (game->level.map[y][x] == 'x') ? ANSI_RED : ANSI_YELLOW); break;
                case '$': printf(ANSI_ORANGE "$" ANSI_RESET); break;
                case 'x': printf(ANSI_RED "x" ANSI_RESET); break;
                case 'O': printf(ANSI_GREEN "O" ANSI_RESET); break;
                default: putchar(game->level.cells[y][x]);
            }
        }
        //Вывод статистики конец первых двух строк уровня
        if(y < 2){
            printf("%s", info[y]);
        }
        
        putchar('\n');
    }
    //Вывод управления
    printf("\n");
    printf("WASD - Move\n");
    printf("F    - Undo\n");
    printf("Q    - Back\n");
}