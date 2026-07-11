#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

#include "../include/menu.h"
#include "../include/game.h"
#include "../include/render.h"

int main_menu(){
    // printf("1. Select level\n2. Quit\n");
    // char select = getchar();
    // switch (select)
    // {
    //     case '1': select_level(); break;
    //     case '2': exit(0);
    //     default: break;
    // }
}

int select_level(MenuLevels levels[MAX_LEVELS]){
    int level_count = get_levels(levels);

    int key;
    int valid_input = 0;
    do{
        printf("\033[2J");
        printf("\033[H");

        printf("====== SELECT LEVEL ======\n\n");

        for (int i = 0; i < level_count; i++)
        {
            printf("%d. %s\n",i+1, levels[i].name);
        }
        printf("\nChoose level number (1-%d)\n", level_count);

        if(scanf("%d", &key) == 1){
            if(key >= 1 && key <= level_count){
                valid_input = 1;
            }
        }
        else{
            getchar();
        }
    }while(!valid_input);

    return key-1;
}

int get_levels(MenuLevels levels[MAX_LEVELS]){
    DIR *dir = opendir("../levels");

    if(dir == NULL){
        perror("Could not find levels directory");
        return 0;
    }

    struct dirent *entry;

    int count = 0;
    
    while ((entry = readdir(dir)) != NULL)
    {
        char *extension = strchr(entry->d_name, '.');
        if (extension == NULL || strcmp(extension, ".txt") != 0) continue;
            
        snprintf(levels[count].path, MAX_LEVEL_PATH, "../levels/%s", entry->d_name);

        FILE *file = fopen(levels[count].path,"r");
        if(file == NULL) continue;

        char line[MAX_LEVEL_NAME + 2];
        if (fgets(line, sizeof(line), file) != NULL) line[strcspn(line, "\r\n")] = '\0';
        strcpy(levels[count].name, line);

        count++;
        if(count >= MAX_LEVELS)
            break;
    }

    closedir(dir);
    qsort(levels, count, sizeof(MenuLevels), compare_levels);
    return count;
}

int compare_levels(const void *a, const void *b)
{
    const MenuLevels *level1 = a;
    const MenuLevels *level2 = b;

    int num1 = 0;
    int num2 = 0;

    sscanf(level1->name, "Level %d", &num1);
    sscanf(level2->name, "Level %d", &num2);

    return num1 - num2;
}