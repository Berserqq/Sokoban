#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "../include/menu.h"
#include "../include/level.h"

int get_levels(char level_names[][MAX_NAME_LENGTH]){
    DIR *dir = opendir("../levels");

    if(dir == NULL){
        perror("Could not find dir \"\\levels\"");
    }

    struct dirent *entry;
    int count = 0;

    while((entry = readdir(dir)) != NULL){
        char *ext = strrchr(entry->d_name, '.');

        if(ext == NULL || strcmp(ext, ".txt") != 0){
            continue;
        }
        strcpy(level_names[count], entry->d_name);

        level_names[count][strlen(level_names[count]) - 4] = '\0';

        count++;

        if (count >= MAX_LEVELS)
            break;
    }

    closedir(dir);

    return count;
}

