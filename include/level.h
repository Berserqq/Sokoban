#ifndef LEVEL_H
#define LEVEL_H

#define MAX_LEVEL_HEIGHT 20
#define MAX_LEVEL_WIDTH 30
#define MAX_LEVEL_NAME 64
#define MAX_LEVEL_PATH 128


typedef struct 
{
    int width;
    int height;

    char cells[MAX_LEVEL_HEIGHT][MAX_LEVEL_WIDTH];
    char map[MAX_LEVEL_HEIGHT][MAX_LEVEL_WIDTH];

    char name[MAX_LEVEL_NAME];
    int passed;

    int total_crates;
}Level;

int level_load(Level *level, char *filename);
int crates_on_map(Level *level);

#endif