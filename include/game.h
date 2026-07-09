#ifndef GAME_H
#define GAME_H
#include "level.h"
#include "menu.h"

typedef struct
{
    Level level;
    

    int player_x;
    int player_y;

    int previous_player_x;
    int previous_player_y;
} Game;

typedef struct 
{
    int moves;
    int boxes;
}Counters;


int player_pos(Game *game);
int max_score(Game *game);
char move_player(Game *game, int vector, Counters *counters);
void last_move(Game *game);
int placed_boxes(Game *game);

#endif