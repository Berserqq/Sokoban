#ifndef MENU_H
#define MENU_H
#define MAX_LEVELS 100
#define MAX_LEVEL_PATH 128
#include "level.h"

typedef struct
{
    char name[MAX_LEVEL_NAME];
    char path[MAX_LEVEL_PATH];
} LevelEntry;


int get_levels(LevelEntry levels[]);
int compare_levels(const void *a, const void *b);
int select_level(LevelEntry levels[], int level_count);

#endif