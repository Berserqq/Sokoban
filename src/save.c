#include <stdio.h>
#include <string.h>
#include "../include/save.h"
#include "../include/game.h"
#include "../include/menu.h"

int save_game(const SaveData *save){
    FILE *file = fopen("savegame.dat", "wb");
    if (!file) return 1;

    fwrite(save, sizeof(SaveData), 1, file);

    fclose(file);

    return 0;
}

int load_game(SaveData *save, Game *game, LevelEntry levels[])
{
    FILE *file = fopen("savegame.dat", "rb");

    if (!file)
        return 0;

    if (fread(save, sizeof(SaveData), 1, file) != 1)
    {
        fclose(file);
        return 0;
    }

    fclose(file);

    if (save->magic != SAVE_MAGIC)
        return 0;

    if (save->version != SAVE_VERSION)
        return 0;

    *game = save->game;

    return 1;
}

int create_new_save(SaveData *save)
{
    memset(save, 0, sizeof(SaveData));

    save->magic = SAVE_MAGIC;
    save->version = SAVE_VERSION;

    save->unlocked_level = 0;
    save->current_level = 0;

    return save_game(save);
}