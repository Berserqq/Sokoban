#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/menu.h"
#include "../include/level.h"

//chat
int get_levels(LevelEntry levels[]){

    DIR *dir = opendir("../levels");

    if(dir == NULL){
        perror("Could not find levels directory");
        return 0;
    }

    struct dirent *entry;

    int count = 0;
    
    while ((entry = readdir(dir)) != NULL)
    {
        char *ext = strchr(entry->d_name, '.');
        if (ext == NULL || strcmp(ext, ".txt") != 0)
            continue;
        
        snprintf(levels[count].path, MAX_LEVEL_PATH, "../levels/%s", entry->d_name);
        strcpy(levels[count].name, entry->d_name);
        levels[count].name[strlen(levels[count].name) - 4] = '\0';

        count++;

        if(count >= MAX_LEVELS)
            break;
    }
    qsort(levels, count, sizeof(LevelEntry), compare_levels);
    closedir(dir);
    return count;
}

int compare_levels(const void *a, const void *b)
{
    const LevelEntry *level1 = a;
    const LevelEntry *level2 = b;

    int num1 = 0;
    int num2 = 0;

    sscanf(level1->name, "Level %d", &num1);
    sscanf(level2->name, "Level %d", &num2);

    return num1 - num2;
}

int select_level(LevelEntry levels[], int level_count){

    int key;
    printf("\033[2J");
    printf("\033[H");
    printf("====== SELECT LEVEL ======\n\n");

    for (int i = 0; i < level_count; i++)
    {
        printf("%d. %s\n",i+1, levels[i].name);
    }

    printf("\nW/S - Select\n");
    printf("Enter - Play\n");

    scanf("%d", &key);

    return key-1;
}
