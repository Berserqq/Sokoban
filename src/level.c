#include <stdio.h>
#include <string.h>
#include "../include/level.h"

int level_load(Level *level, char *filename){
    FILE *file = fopen(filename, "r");

    if (file == NULL) return 1;


    char line[MAX_WIDTH + 2]; //+2 cuz of special symbols like /n

    level-> width = 0;
    level-> height = 0;

    while(fgets(line, sizeof(line),file)){
        line[strcspn(line, "\n")] = '\0';

        if(level->width < strlen(line))
            level->width = strlen(line);

        for(int i = 0; i < level->width; i++){
            level->cells[level->height][i] = line[i];
            level->map[level->height][i] = line[i];
        }

        level->height++;
    }

    for(int i = 0; i < level->height; i++){
        for(int j = 0; j < level->width; j++){
            if(level->map[i][j] == '$' || level->map[i][j] == '@'){
                level->map[i][j] = ' ';
            }
        }
    }

    fclose(file);
    return 0;
}

