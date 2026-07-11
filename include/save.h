/**
 * @file save.h
 * @brief Заголовочный файл системы сохранений
 * 
 * Определяет структуру данных Save для сохранения прогресса уровня.
 * Определеяет прототипы функций для загрузки и сохранения данных
 */

#ifndef SAVE_H
#define SAVE_H

#include "game.h"
#include "menu.h"


#define SAVE_FILE "save.dat"


typedef struct
{
    char level_name[MAX_LEVEL_NAME];
    int best_moves;
} Save;

void load_save(Save save[MAX_LEVELS], MenuLevels levels[MAX_LEVELS], int level_count);
void save_game(Save save[MAX_LEVELS]);

#endif