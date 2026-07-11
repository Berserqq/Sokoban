#include <stdio.h>
#include <string.h>

#include "../include/game.h"
#include "../include/level.h"
#include "../include/input.h"


int player_position(Game *game){
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

int move_player(Game *game, int vector){
    int dx = 0;
    int dy = 0;

    switch (vector)
    {
        case KEY_UP: dy = -1; break;
        case KEY_LEFT: dx = -1; break;
        case KEY_DOWN: dy = 1; break;
        case KEY_RIGHT: dx = 1; break;
        default: return 0;
    }

    int new_x = game->player_x + dx;
    int new_y = game->player_y + dy;


    char *target = &game->level.cells[new_y][new_x];
    char *next = &game->level.cells[new_y + dy][new_x + dx];

    char *player = &game->level.cells[game->player_y][game->player_x];
    char *player_map = &game->level.map[game->player_y][game->player_x];

    if(*target == '#' || ((*target == '$' || *target == 'O') && (*next == '#' || *next == '$' || *next == 'O'))){
        return 0;
    }

    memcpy(game->last_cells, game->level.cells, sizeof(game->level.cells));
    game->last_player_x = game->player_x;
    game->last_player_y = game->player_y;
    
    if(*target == '$' || *target ==  'O'){
        if(*next == ' ' || *next == 'x'){
            *next = (*next == ' ') ? '$' : 'O';
        }
    }    

    game->level.cells[game->player_y][game->player_x] = (*player_map == 'x') ? 'x' : ' ';
    *target = '@';

    game->player_x = new_x;
    game->player_y = new_y; 
    game->moves++;
}

void last_move(Game *game){
    int equal = 1;
    for(int i = 0; i < game->level.height; i++){
        for(int j = 0; j < game->level.width; j++){
            if(game->last_cells[i][j] != game->level.cells[i][j]){
                equal = 0;
                break;
            }
        }
        if(equal == 0){
            break;
        }
    }
    if(equal || game->moves == 0) return;
    memcpy(game->level.cells, game->last_cells, sizeof(game->last_cells));

    game->player_x = game->last_player_x; 
    game->player_y = game->last_player_y;
    game->moves--;
}

int crates_on_targets(Game *game){
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

