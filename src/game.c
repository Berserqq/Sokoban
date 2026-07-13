/**
 * @file game.c
 * @brief Реализация логики перемещения персонажем и управления состоянием игры
 * 
 * Содержит сканирование позиции игрока, обработку колизий игрока с ящиками и стенами, изменение ячеек карты при передвижении и откат состояния уровня на ход назад.
 */

#include <stdio.h>
#include <string.h>

#include "../include/game.h"
#include "../include/level.h"
#include "../include/input.h"


int player_position(Game *game){
    int players = 0;
    for(int y = 0; y < game->level.height; y++){
        for(int x = 0; x < game->level.width; x++){
            if(game->level.cells[y][x] == '@'){
                game->player_y = y;
                game->player_x = x;
                players++;
            }
        }
    }
    return players;
}

void move_player(Game *game, int vector){
    int dx = 0;
    int dy = 0;

    //Обработка ввода
    switch (vector)
    {
        case KEY_UP: dy = -1; break;
        case KEY_LEFT: dx = -1; break;
        case KEY_DOWN: dy = 1; break;
        case KEY_RIGHT: dx = 1; break;
        default: return;
    }

    //Определение новых координат игрока
    int new_x = game->player_x + dx;
    int new_y = game->player_y + dy;

    //Указатели для сокращения длинных переменных
    char *target = &game->level.cells[new_y][new_x];
    char *next = &game->level.cells[new_y + dy][new_x + dx];

    char *player = &game->level.cells[game->player_y][game->player_x];
    char *player_map = &game->level.map[game->player_y][game->player_x];

    //Обработка коллизий
    if(*target == '#' || ((*target == '$' || *target == 'O') && (*next == '#' || *next == '$' || *next == 'O'))){
        return;
    }

    //Копирование состояния игры для возможности вернуть предыдущее состояние уровня
    memcpy(game->last_cells, game->level.cells, sizeof(game->level.cells));
    game->last_player_x = game->player_x;
    game->last_player_y = game->player_y;
    
    //Проверка целевой клетки на наличие ящика
    if(*target == '$' || *target ==  'O'){
        if(*next == ' ' || *next == 'x'){
            //Если целевая клетка - ящик, то ящик перемещается на клетку за ней
            *next = (*next == ' ') ? '$' : 'O';
        }
    }    

    //Восстанавление клетки, на которой стоял игрок
    game->level.cells[game->player_y][game->player_x] = (*player_map == 'x') ? 'x' : ' ';
    //Перемещенеие модели игрока на целевую клетку
    *target = '@';

    //Обновление координат игрока
    game->player_x = new_x;
    game->player_y = new_y; 
    //Обновление счетчиков ходов
    game->moves++;
}

void last_move(Game *game){
    int equal = 1;
    //Цикл для проверки совпадения состояний карты
    for(int i = 0; i < game->level.height; i++){
        for(int j = 0; j < game->level.width; j++){
            if(game->last_cells[i][j] != game->level.cells[i][j]){
                equal = 0;
                break;
            }
        }
        if(equal == 0){
            break;
        }
    }
    //Проверка на совпадение состояний и начала игры
    if(equal || game->moves == 0) return;

    //Обновление состояния игры
    memcpy(game->level.cells, game->last_cells, sizeof(game->last_cells));
    game->player_x = game->last_player_x; 
    game->player_y = game->last_player_y;
    game->moves--;
}

int crates_on_targets(Game *game){
    int targets = 0;
    for(int y = 0; y < game->level.height; y++){
        for(int x = 0; x < game->level.width; x++){
            if(game->level.cells[y][x] == 'O'){
                targets++;
            }
        }
    }
    return targets;
}

