#ifndef LEVEL_H
#define LEVEL_H

#define MAX_WIDTH 30
#define MAX_HEIGHT 20
#define MAX_LEVEL_NAME 71

typedef struct 
{
    int width;
    int height;
    char cells[MAX_HEIGHT][MAX_WIDTH];
    char previous_cells[MAX_HEIGHT][MAX_WIDTH];
    char map[MAX_HEIGHT][MAX_WIDTH];
    char name[MAX_LEVEL_NAME];
} Level;


int level_load(Level *level, char *filename);

#endif