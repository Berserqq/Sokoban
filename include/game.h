#ifndef GAME_H
#define GAME_H
#include "level.h"


typedef struct
{
    Level level;
    
    int player_x;
    int player_y;

    int previous_player_x;
    int previous_player_y;
} Game;

int player_pos(Game *game);
int max_score(Game *game);
char move_player(Game *game, int vector);
int last_move(Game *game);
int level_completed(Game *game, int max_score);

#endif