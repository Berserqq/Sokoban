/**
 * @file save.c
 * @brief Реализация системы сохранений
 */

#include <stdio.h>
#include <string.h>

#include "../include/save.h"


void load_save(Save save[MAX_LEVELS], MenuLevels levels[MAX_LEVELS], int level_count) {
    //Заполнение массива на случай поврежденного файла сохранения
    memset(save, 0, sizeof(Save) * MAX_LEVELS);
    for (int i = 0; i < level_count; i++) {
        strcpy(save[i].level_name, levels[i].name);
        save[i].best_moves = 0;
    }

    //Если файла сохранения нет, то загружаемся с чистой статистикой
    FILE *file = fopen(SAVE_FILE, "rb");
    if (file == NULL) {
        return; 
    }

    //Проверка заголовка
    SaveHeader header;
    if (fread(&header, sizeof(SaveHeader), 1, file) != 1) {
        fclose(file);
        return;
    }

    //Проверка SAVE_MAGIC и версии сохранения файла
    if (strncmp(header.magic, SAVE_MAGIC, SAVE_MAGIC_LEN) != 0 || header.version != SAVE_VERSION) {
        fclose(file);
        return; // Файл некорректен — игнорируем его ради безопасности
    }

    //Буфферная структура для чтения файла сохранения
    Save loaded_data[MAX_LEVELS];
    memset(loaded_data, 0, sizeof(Save) * MAX_LEVELS);
    //size_t - беззнаковый целочисленный тип. fread возвращает значение такого типа
    size_t read_count = fread(loaded_data, sizeof(Save), header.record_count, file);
    fclose(file);

    //Запись рекордов уровней в соответствии с их именами
    for (int i = 0; i < level_count; i++) {
        for (size_t j = 0; j < read_count; j++) {
            if (strcmp(save[i].level_name, loaded_data[j].level_name) == 0) {
                save[i].best_moves = loaded_data[j].best_moves;
                levels[i].best_moves = loaded_data[j].best_moves;
                break;
            }
        }
    }
}

//
void save_game(Save save[MAX_LEVELS], int level_count){
    FILE *file = fopen(SAVE_FILE, "wb");
    if(file == NULL){
        perror("Failed to save game");
        return;
    }

    SaveHeader header;
    memcpy(header.magic, SAVE_MAGIC, SAVE_MAGIC_LEN);
    header.version = SAVE_VERSION;
    fwrite(&header, sizeof(SaveHeader), 1, file);
    fwrite(save, sizeof(Save), MAX_LEVELS, file);
    fclose(file);
}