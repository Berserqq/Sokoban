/**
 * @file main.c
 * @brief Точка входа в игру Sokoban
 */

#include <stdio.h>
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
        for(int i = 0; i < level_count; i++) {
            passed[i] = (save[i].best_moves > 0) ? 1 : 0;
        }
        int selected = select_level(levels, passed, level_count);
        
        // strcpy(save[selected].level_name, levels[selected].name);
        start_game(levels[selected].path, &save[selected]);
        save_game(save, level_count);
    }
}

void start_game(char level_path[MAX_LEVEL_PATH], Save *save){
    Game game;
    memset(&game, 0, sizeof(game));
    
    if(level_load(&game.level, level_path)){
        printf("Invalid level\n");
        getchar();
        return;
    }

    input_init();
    player_position(&game);

    while (game.level.total_crates > crates_on_targets(&game))
    {
        int key = player_input();

        if(key == KEY_ESCAPE){
            input_shutdown();
            return;
        }
        if(key == KEY_LAST_MOVE){
            last_move(&game);
        }
        move_player(&game, key);
        render_level(&game);
    }
    input_shutdown();
    if(game.moves < save->best_moves || save->best_moves == 0){
        save->best_moves = game.moves;
    }
    
    printf("\033[2J\033[HCongratulations!\nMoves: %d", game.moves);
    getchar();
    return;
}