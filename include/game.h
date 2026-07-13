/**
 * @file game.h
 * @brief Заголовочный файл основного игрового цикла и логики перемещений.
 * 
 * Определяет структуру состояния игры.
 * Определяет функции поиска игрока, движения игрока, последнего хода и поиска поставленных на цели ящиков
 */

#ifndef GAME_H
#define GAME_H

#include "level.h"
#include "input.h"



typedef struct
{
    Level level;
    Input input;

    int player_y;
    int player_x;

    int last_player_y;
    int last_player_x;

    int moves;
    int crates;

    char last_cells[MAX_LEVEL_HEIGHT][MAX_LEVEL_WIDTH];
    
} Game;

int player_position(Game *game);
int move_player(Game *game, int vector);
void last_move(Game *game);
int crates_on_targets(Game *game);

#endif