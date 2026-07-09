#ifndef SAVE_H
#define SAVE_H

#include "game.h"
#include "menu.h"

#define SAVE_MAGIC 0x534F4B4F  // "SOKO"
#define SAVE_VERSION 1

typedef struct 
{
    int magic;
    int version;

    int has_save;

    int unlocked_level;
    int current_level;

    int best_moves[MAX_LEVELS];

    Game game;
}SaveData;

int save_game(const SaveData *save);
int load_game(SaveData *save, Game *game, LevelEntry level[]);
int create_new_save(SaveData *save);

#endif