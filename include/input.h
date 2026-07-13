/**
 * @file input.h
 * @brief Заголовочный файл для системы ввода.
 * 
 * Содержит коды клавиш, функции обработки ввода и считывания нажатий в реальном времени, без ожидания клавиши Enter.
 */

#ifndef INPUT_H
#define INPUT_H
#include <stdio.h>

/**
 * @enum Input
 * @brief Коды поддерживаемых клавш.
 */
typedef enum{
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_ENTER,
    KEY_ESCAPE,
    KEY_LAST_MOVE
} Input;

/**
 * @brief Опрашивает клавиатуру и возвращает коды клавиш
 * 
 * @return int Коды клавиши из перечисления @ref Input
 */
int player_input(void);

/** 
 * @brief Инициализирует консоль для мгновенного чтения ввода
 */
void input_init(void);

/**
 * @brief Восстанавливает настройки терминала
 */
void input_shutdown(void);

#endif