#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../include/level.h"
#include "../include/game.h"
#include "../include/render.h"
#include "../include/input.h"
#include "../include/menu.h"
#include "../include/save.h"

void start_level(Game *game, LevelEntry levels[MAX_LEVELS], int level_count, Counters *counters, SaveData *save);
void start_game(Game *game, LevelEntry *levels, int level_number, int level_count, Counters *counters, SaveData *save);

int main(){
    LevelEntry levels[MAX_LEVELS];
    Game game;
    Counters counters;
    SaveData save;

    if (!load_game(&save, &game, levels))
    {
        create_new_save(&save);
    }
    load_game(&save, &game, levels);

    counters.moves = 0;

    int level_count = get_levels(levels);
    start_level(&game, levels, level_count, &counters, &save);
    return 0;
    
}
void start_level(Game *game, LevelEntry levels[MAX_LEVELS], int level_count, Counters *counters, SaveData *save){
    
    int selected = select_level(levels, level_count);    

    level_load(&game->level, levels[selected].path);
    printf("Opening level %s\n", levels[selected].name);
    int players = player_pos(game);
    if(players == 0){
        system("clear");
        printf("Could not find player.\n");
        start_level(game, levels, level_count, counters, save);
    }
    else if(players > 1){
        system("clear");
        printf("Multiple players found\n");
        start_level(game, levels, level_count, counters, save);
    }
    strcpy(game->level.name, levels[selected].name);
    start_game(game, levels, selected, level_count, counters, save);
}

void start_game(Game *game, LevelEntry *levels, int level_number, int level_count, Counters *counters, SaveData *save){
    system("clear");
    input_init();
    atexit(input_shutdown);
    render_level(game, counters);
    while(placed_boxes(game) < max_score(game)){

        render_level(game, counters);
        int key = player_input();
        if(key == KEY_LAST_MOVE){
            last_move(game);
            continue;
        }
        if(key == KEY_ESCAPE){
            input_shutdown();
            start_level(game, levels, level_count, counters, save);
        }
        move_player(game, key, counters);
    }

    save->game = *game;
    input_shutdown();
    system("clear");
    render_level(game, counters);
    sleep(1);
    printf("Congrats!\n");
    sleep(1);
    start_level(game, levels, level_count, counters, save);
}

