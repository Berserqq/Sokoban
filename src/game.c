#include <stdio.h>
#include <string.h>
#include "../include/game.h"
#include "../include/level.h"
#include "../include/render.h"
#include "../include/input.h"

int player_pos(Game *game){
    int players = 0;

    for(int y = 0; y < game->level.height; y++){
        for(int x = 0; x < game->level.width; x++){
            if(game->level.cells[y][x] == '@'){
                game->player_y = y;
                game->player_x = x;
                players++;
            }
        }
    }
    return players;
}

int max_score(Game *game){
    int max_score = 0;

    for(int y = 0; y < game->level.height; y++){
        for(int x = 0; x < game->level.width; x++){
            if(game->level.map[y][x] == 'x'){
                max_score++;
            }
        }
    }
    return max_score;
}

char move_player(Game *game, int vector, Counters *counters){
    
    int dx = 0;
    int dy = 0;

    switch (vector)
    {
        case KEY_UP: dy = -1; break;
        case KEY_LEFT: dx = -1; break;
        case KEY_DOWN: dy = 1; break;
        case KEY_RIGHT: dx = 1; break;
        default: return 1;
    }

    int new_x = game->player_x + dx;
    int new_y = game->player_y + dy;


    char *target = &game->level.cells[new_y][new_x];
    char *next = &game->level.cells[new_y + dy][new_x + dx];

    char *player = &game->level.cells[game->player_y][game->player_x];
    char *player_map = &game->level.map[game->player_y][game->player_x];

    if(*target == '#' || ((*target == '$' || *target == 'O') && (*next == '#' || *next == '$' || *next == 'O'))){
        return 1;
    }

    memcpy(game->level.previous_cells, game->level.cells, sizeof(game->level.cells));
    game->previous_player_x = game->player_x;
    game->previous_player_y = game->player_y;
    
    if(*target == '$' || *target ==  'O'){
        if(*next == ' ' || *next == 'x'){
            *next = (*next == ' ') ? '$' : 'O';
        }
    }    

    game->level.cells[game->player_y][game->player_x] = (*player_map == 'x') ? 'x' : ' ';
    *target = '@';

    game->player_x = new_x;
    game->player_y = new_y;
    counters->moves++;
    return 1;
}

void last_move(Game *game){
    memcpy(game->level.cells, game->level.previous_cells, sizeof(game->level.previous_cells));
    game->player_x = game->previous_player_x; 
    game->player_y = game->previous_player_y;
}

int placed_boxes(Game *game){
    int targets = 0;
    for(int y = 0; y < game->level.height; y++){
        for(int x = 0; x < game->level.width; x++){
            if(game->level.cells[y][x] == 'O'){
                targets++;
            }
        }
    }
    
    return targets;
}