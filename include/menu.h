/**
 * @file menu.h
 * @brief Заголовочный файл системы выбора уровня.
 * 
 * Определяет структуруу хранения списка доступных уровней, функции сканирования директории ../levels и выбора уровня.
 */

#ifndef MENU_H
#define MENU_H

#define MAX_LEVELS 100

#include "level.h"

/** @struct MenuLevels
 * @brief Элемент списка уровней в меню.
 * 
 * Хранит информацию о пути и имени уровня, которая используется для выбора уровня в меню.
 */
typedef struct
{
    char path[MAX_LEVEL_PATH];
    char name[MAX_LEVEL_NAME];
    int best_moves;
}MenuLevels;

/** @brief Отображает меню уровней и обрабатывает ввод игрока для выбора.
 * 
 * Выводит список доступных уровней, подсвечивает пройденные уровни.
 */
int select_level(MenuLevels levels[MAX_LEVELS], int passed[MAX_LEVELS], int level_count);

/**
 * @brief Сканирует директорию с картами и заполняет массив уровней.
 * 
 * Ищет текстовые файлы в папке ../levels, записывает путь к файлу в path, открывает файл и записывает первую строку в name.
 * 
 * @param[out] levels Массив структур MenuLevels для заполнения.
 * @return int Количество найденных уровней.
 */
int get_levels(MenuLevels levels[MAX_LEVELS]);


#endif