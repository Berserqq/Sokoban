/**
 * @file main.c
 * @brief Точка входа в игру Sokoban
 */

#include <stdio.h>
#include <stdlib.h>>
#include <string.h>

#include "../include/level.h"
#include "../include/game.h"
#include "../include/render.h"
#include "../include/menu.h"
#include "../include/save.h"

/**
 * @brief Запускает игровой сеанс для конкретного уровня.
 * 
 * @param[in] level_path Путь к файлу уровня.
 * @param[in,out] save   Указатель на структуру сохранения для записи нового рекорда.
 */
void start_game(char level_path[MAX_LEVEL_PATH], Save *save);

int main(void){
    
    MenuLevels levels[MAX_LEVELS];
    Save save[MAX_LEVELS];

    //Загружаем список уровней, имена и пути из директории ../levels
    int level_count = get_levels(levels);

    //Загружаем сохранение с диска
    load_save(save, levels, level_count);

    int passed[MAX_LEVELS];

    //Основной цикл
    while (1)
    {
        //Присвоение рекордов уровней для меню
        for(int i = 0; i < level_count; i++) {
            passed[i] = (save[i].best_moves > 0) ? 1 : 0;
            levels[i].best_moves = save[i].best_moves;
        }

        //Показ меню выбора уровня и получение ввода пользователя
        int selected = select_level(levels, passed, level_count);
        //Запуск выбранного уровня
        start_game(levels[selected].path, &save[selected]);
        //Сохранения рекордов после прохождения уровня или выхода из него
        save_game(save, level_count);
    }
}

void start_game(char level_path[MAX_LEVEL_PATH], Save *save){
    Game game;
    memset(&game, 0, sizeof(game));
    
    //Безопасная загрузка уровня.
    if(level_load(&game.level, level_path)){
        printf("Invalid level\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }
    //Инициализвация системы ввода
    input_init();
    //Нахождение координат игрока
    player_position(&game);

    //Цикл уровня: выход если уровень пройден или нажата клавиша выхода
    while (game.level.total_crates > crates_on_targets(&game))
    {
        //Ввод игрока
        int key = player_input();

        //Выход из уровня
        if(key == KEY_ESCAPE){
            input_shutdown();
            return;
        }
        //Отмена хода
        else if(key == KEY_LAST_MOVE){
            last_move(&game);
        }
        //Обработка передвижения
        else move_player(&game, key);
        render_level(&game);
    }
    //Возврат настроек терминала по умолчанию
    input_shutdown();
    //Обновление рекорда уровня
    if(game.moves < save->best_moves || save->best_moves == 0){
        save->best_moves = game.moves;
    }
    
    //Вывод поздравления
    system("clear");
    printf("=========================\n");
    printf("     CONGRATULATIONS!    \n");
    printf("=========================\n");
    printf("You completed the level in %d moves!\n", game.moves);
    if (game.moves <= save->best_moves) {
        printf(ANSI_GREEN "NEW PERSONAL BEST!" ANSI_RESET "\n");
    }
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return;
}