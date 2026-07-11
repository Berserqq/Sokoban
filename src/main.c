#include <stdio.h>
#include <string.h>

#include "../include/level.h"
#include "../include/game.h"
#include "../include/render.h"
#include "../include/menu.h"

void start_game(char level_path[MAX_LEVEL_PATH],MenuLevels levels[MAX_LEVEL_PATH]);

int main(){
    MenuLevels levels[MAX_LEVEL_PATH];

    while (1)
    {
        int selected = select_level(levels);

        start_game(levels[selected].path, levels);
    }
}

void start_game(char level_path[MAX_LEVEL_PATH],MenuLevels levels[MAX_LEVEL_PATH]){
    Game game;
    memset(&game, 0, sizeof(game));
    level_load(&game.level, level_path);

    input_init();
    render_level(&game);
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
    printf("\033[2J\033[H Congratulations!");
    getchar();
    return;
}