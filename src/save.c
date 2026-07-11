#include <stdio.h>
#include <string.h>

#include "../include/save.h"
/**
 * @file save.c
 * @brief 
 */

/**
 * @brief Загружает сохранение из бинарного файла на диске.
 * 
 * Функция пытается открыть файл в режиме бинарного чтения.
 * Если файл существует, то записывает данные из файла в save.
 * Если файла не существует, то записывает в массив save имена уровней и зануляет статистику.
 * 
 * @param[out] save         Массив структур для загруженных из файла сохранения данных.
 * @param[in] levels        Массив уровней.
 * @param[in] level_count   Количество найденных уровней.
 */

void load_save(Save save[MAX_LEVELS], MenuLevels levels[MAX_LEVELS], int level_count){
    FILE *file = fopen(SAVE_FILE, "rb");
    if(file != NULL){
        fread(save, sizeof(Save), MAX_LEVELS, file);
        fclose(file);
    }
    else{
        memset(save, 0, sizeof(Save) * MAX_LEVELS);
        for(int i = 0; i < level_count; i++){
            strncpy(save[i].level_name, levels[i].name, MAX_LEVEL_NAME - 1);
            save[i].best_moves = 0;
        }
    }
}

/**
 * @brief Создает сохранения в виде бинарного файла
 * 
 * Открывает файл в режиме 
 */

void save_game(Save save[MAX_LEVELS]){
    FILE *file = fopen(SAVE_FILE, "wb");
    if(file == NULL){
        perror("Failed to save game");
        return;
    }
    fwrite(save, sizeof(Save), MAX_LEVELS, file);
    fclose(file);
}