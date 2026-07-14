/**
 * @file save.c
 * @brief 
 */

#include <stdio.h>
#include <string.h>

#include "../include/save.h"


void load_save(Save save[MAX_LEVELS], MenuLevels levels[MAX_LEVELS], int level_count){
    FILE *file = fopen(SAVE_FILE, "rb");
    if(file != NULL){
        //Считывает заданное количество элементов данных из бинарного файла в буфер
        fread(save, sizeof(Save), MAX_LEVELS, file);
        fclose(file);
    }
    else{
        //Заполняет структуру save нулями, так как иначе может содержать мусор от предыдущего владельца память
        memset(save, 0, sizeof(Save) * MAX_LEVELS);
        //Цикл, заполняющий имена, и зануляющий статистику.
        for(int i = 0; i < level_count; i++){
            //strncpy копирует заданное количество символов, в отличие от strcpy. Используется во 
            strcpy(save[i].level_name, levels[i].name);
            save[i].best_moves = 0;
        }
    }
}

//
void save_game(Save save[MAX_LEVELS]){
    FILE *file = fopen(SAVE_FILE, "wb");
    if(file == NULL){
        perror("Failed to save game");
        return;
    }

    SaveHeader header;
    memccpy(header.magic, SAVE_MAGIC, SAVE_MAGIC_LEN);
    header.version = SAVE_VERSION;
    fwrite(&header, sizeof(SaveHeader), 1, file);
    fwrite(save, sizeof(Save), MAX_LEVELS, file);
    fclose(file);
}