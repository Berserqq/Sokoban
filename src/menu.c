/**
 * @file menu.c
 * @brief Реализация системы выбора уровня
 */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

#include "../include/menu.h"
#include "../include/game.h"
#include "../include/render.h"

/*
Внутренняя функция сортировки уровня для qsort.
Сравнивает числа после "Level" в названии.
*/
static int compare_levels(const void *a, const void *b)
{
    const MenuLevels *level1 = a;
    const MenuLevels *level2 = b;

    int num1 = 0;
    int num2 = 0;

    sscanf(level1->name, "Level %d", &num1);
    sscanf(level2->name, "Level %d", &num2);

    return num1 - num2;
}

int select_level(MenuLevels levels[MAX_LEVELS], int passed[MAX_LEVELS], int level_count){
    int key;
    int valid_input = 0;
    //do while позволяет выводить меню до ввода игрока
    do{
        system("clear");
        printf("====== SELECT LEVEL ======\n\n");

        //Цикл для вывода списка уровней
        for (int i = 0; i < level_count; i++)
        {
            /*Подсветка пройденных уровней.
            Уровень считается пройденным, если есть запись о лучшем количестве ходов.
            Выводит: <номер уровня> | <название уровня> | <лучший счет>
            */
            if(passed[i]) printf(ANSI_GREEN "%-2d| %-20s| %d" ANSI_RESET,i+1, levels[i].name, levels[i].best_moves);
            else printf("%-2d| %-20s| %d",i+1, levels[i].name, levels[i].best_moves);
            putchar('\n');
        }
        printf("\nChoose level number (1-%d)\n", level_count);

        //Проверка валидности ввода
        if(scanf("%d", &key) == 1){
            if(key >= 1 && key <= level_count){
                valid_input = 1;
            }
        }
        else{
            getchar();
        }
    }while(!valid_input);

    //Возвращает номер уровня
    return key-1;
}

//Функция, достающая названия уровней и их пути для списка уровней
int get_levels(MenuLevels levels[MAX_LEVELS]){
    //Открывает директорию ../levels
    DIR *dir = opendir("../levels");
    //Если уровней нет - выводит ошибку.
    if(dir == NULL){
        perror("Could not find levels directory");
        return 0;
    }

    //Структура для записи информации о открытом файле
    struct dirent *entry;

    //Переменная количества уровней
    int count = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        //Проверка расширения файла.
        char *extension = strchr(entry->d_name, '.');
        if (extension == NULL || strcmp(extension, ".txt") != 0) continue;
        
        //Добавление пути уровня в список уровней
        snprintf(levels[count].path, MAX_LEVEL_PATH, "../levels/%s", entry->d_name);

        //Открытие файла уровня для считывания имени уровня
        FILE *file = fopen(levels[count].path,"r");
        if(file == NULL) continue;

        char line[MAX_LEVEL_NAME + 2];
        //Построчное считывание файла
        if (fgets(line, sizeof(line), file) != NULL) line[strcspn(line, "\r\n")] = '\0';

        //Защита от слишком длинного имени
        line[MAX_LEVEL_NAME-1] = '\0';
        strcpy(levels[count].name, line);

        count++;
        //Ограничение количества записываемых уровней
        if(count >= MAX_LEVELS)
            break;
    }

    closedir(dir);
    //Сортировка списка уровней по числу в имени уровня
    qsort(levels, count, sizeof(MenuLevels), compare_levels);
    return count;
}

