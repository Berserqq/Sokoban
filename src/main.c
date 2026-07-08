#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../include/level.h"
#include "../include/game.h"
#include "../include/render.h"
#include "../include/input.h"
#include "../include/menu.h"

void start_level(Game *game, LevelEntry levels[MAX_LEVELS], int level_count);
void start_game(Game *game, LevelEntry *levels, int level_number, int level_count);

int main(){
    LevelEntry levels[MAX_LEVELS];
    Game game;
    int level_count = get_levels(levels);
    start_level(&game, levels, level_count);
    return 0;
    
}
void start_level(Game *game, LevelEntry levels[MAX_LEVELS], int level_count){
    
    int selected = select_level(levels, level_count);    

    level_load(&game->level, levels[selected].path);
    printf("Opening level %s\n", levels[selected].name);
    int players = player_pos(game);
    if(players == 0){
        system("clear");
        printf("Could not find player.\n");
        start_level(game, &levels[selected], level_count);
    }
    else if(players > 1){
        system("clear");
        printf("Multiple players found\n");
        start_level(game, &levels[selected], level_count);
    }
    start_game(game, levels, selected, level_count);
}

void start_game(Game *game, LevelEntry *levels, int level_number, int level_count){
    system("clear");
    input_init();
    atexit(input_shutdown);
    render_level(game);
    while(!level_completed(game, max_score(game))){
        
        render_level(game);
        int key = player_input();
        if(key == KEY_LAST_MOVE){
            last_move(game);
            continue;
        }
        if(key == KEY_ESCAPE){
            input_shutdown();
            start_level(game, levels, level_count);
        }
        move_player(game, key);
    }
    input_shutdown();
        render_level(game);
    sleep(0.5);
    
    strcat(levels[level_number].name, " passed");
    system("clear");
    printf("Congrats!\n");
    sleep(1);
    start_level(game, levels, level_count);
}

