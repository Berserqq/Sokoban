/**
 * @file level.c
 * @brief 
 */

#include <stdio.h>
#include <string.h>

#include "../include/level.h"

static int total_crates(Level *level){
        int crates = 0;

    for(int y = 0; y < level->height; y++){
        for(int x = 0; x < level->width; x++){
            if(level->map[y][x] == 'x'){
                crates++;
            }
        }
    }
    level->total_crates = crates;
    return 0;
}

void level_load(Level *level, char *filename){
    FILE *file = fopen(filename, "r");
    if (file == NULL) return;

    char line[MAX_LEVEL_NAME + 2];
    level->width = 0;
    level->height = 0;
    fgets(line, sizeof(line),file);

    if(strlen(line) > MAX_LEVEL_NAME){
        while (fgetc(file) != '\n');
    }

    line[MAX_LEVEL_NAME-1] = '\n';

    strcpy(level->name, line);

    while(fgets(line, sizeof(line),file)){
        line[strcspn(line, "\n")] = '\0';

        if(level->width < strlen(line))
            level->width = strlen(line);

        for(int i = 0; i < level->width; i++){
            level->cells[level->height][i] = line[i];
            level->map[level->height][i] = line[i];

            if(level->map[level->height][i] == '$' || level->map[level->height][i] == '@'){
                level->map[level->height][i] = ' ';
            }
        }

        level ->height++;
    }
    fclose(file);
    total_crates(level);
    return;
}

