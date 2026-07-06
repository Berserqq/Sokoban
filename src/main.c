#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/level.h"
#include "../include/game.h"
#include "../include/render.h"
#include "../include/input.h"


int main(){
    Game game;
    level_load(&game.level ,"../levels/level02.txt");
    int players = player_pos(&game);
    if(players == 0){
        printf("Could not find player.\n");
        return 1;
    }
    else if(players > 1){
        printf("Multiple players found");
        return 1;
    }

    render_level(&game);
    while(!level_completed(&game, max_score(&game))){
        int key = player_input();
        render_level(&game);
        if(key == 5){
            last_move(&game);
            continue;
        }
        move_player(&game, key);

    }

    render_level(&game);
    sleep(1);
    system("clear");
    printf("Congrats!\n");
}

