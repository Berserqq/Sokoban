/**
 * @file level.c
 * @brief Реализация загрузки и хранения уровня
 */

#include <stdio.h>
#include <string.h>

#include "../include/level.h"

static void total_crates(Level *level){
        int crates = 0;

    for(int y = 0; y < level->height; y++){
        for(int x = 0; x < level->width; x++){
            if(level->map[y][x] == 'x'){
                crates++;
            }
        }
    }
    level->total_crates = crates;
}

int level_load(Level *level, char *filename){
    FILE *file = fopen(filename, "r");
    if (file == NULL) return 1;

    char line[MAX_LEVEL_NAME + 2];
    level->width = 0;
    level->height = 0;

    //Считывание первой строки для записи названия уровня
    fgets(line, sizeof(line),file);

    //Очистка строки, если выходит за пределы максимального названия уровня
    if(strlen(line) > MAX_LEVEL_NAME){
        while (fgetc(file) != '\n');
    }
    
    line[MAX_LEVEL_NAME-1] = '\n';
    strcpy(level->name, line);

    //Цикл выгрузки уровня из .txt в матрицу уровня
    while(fgets(line, sizeof(line),file)){
        
        line[strcspn(line, "\n")] = '\0';
        //Проверка валидности уровня по максимальной ширине
        if(strlen(line) > MAX_LEVEL_WIDTH){
            fclose(file);
            return 1;
        }

        //Установка ширины уровня
        if(level->width < strlen(line))
            level->width = strlen(line);
        
        //Заполнение уровня символами
        for(int i = 0; i < level->width; i++){
            level->cells[level->height][i] = line[i];
            level->map[level->height][i] = line[i];

            //Удаление символов ящика и игрока со статичной карты
            if(level->map[level->height][i] == '$' || level->map[level->height][i] == '@'){
                level->map[level->height][i] = ' ';
            }
        }
        
        level ->height++;
    }

    fclose(file);
    total_crates(level);
    //Проверка валидности уровня по признаку максимальной высоты.
    if(level->height > MAX_LEVEL_HEIGHT) return 1;
    return 0;
}

