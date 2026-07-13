/**
 * @file render.h
 * @brief Заголовочный файл системы отрисовки игрового интерфейса.
 * 
 * Определяет функции графического отображения игры в консоли, а также цветовые ANSI-палитры для стилизации отрисовки.
 */

#ifndef RENDER_H
#define RENDER_H

#include "game.h"

#define ANSI_GREEN  "\033[32m"
#define ANSI_RED    "\033[31m"
#define ANSI_YELLOW "\033[33m"
#define ANSI_BLUE   "\033[34m"
#define ANSI_ORANGE "\033[38;5;208m"
#define ANSI_RESET  "\033[0m"

/** @brief Отрисовывает динамическую карту, количество ходов, ящиков, и управление
 * 
 * Выводит метаданные (название уровня, количество ходов, ящиков и управление), поклеточно отрисовывает матрицу 'game->level.cells'.
 * 
 * @param[in] game Указатель на структуру состояния игры
 */
void render_level(Game *game);

#endif