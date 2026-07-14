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

/** 
 * @brief Имя бинарного файла для записи и чтения прогресса
 */
#define SAVE_FILE "save.dat"
#define SAVE_MAGIC "SOKO"
#define SAVE_MAGIC_LEN 4
#define SAVE_VERSION 1

/**
 * @struct Save
 * @brief Структура, хранящая имя уровня и показатель лучшего результата уровня
 */
typedef struct
{
    char level_name[MAX_LEVEL_NAME];
    int best_moves;
} Save;

/** @struct SaveHeader
 * @brief Заголовок файла сохранения для проверки целостности.
 */
typedef struct 
{
    char magic[SAVE_MAGIC_LEN]; /**< Должно быть "SOKO" */
    int version; /**< Версия формата сохранения */
} SaveHeader;


void load_save(Save save[MAX_LEVELS], MenuLevels levels[MAX_LEVELS], int level_count);
void save_game(Save save[MAX_LEVELS]);

#endif