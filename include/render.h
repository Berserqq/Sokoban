#ifndef RENDER_H
#define RENDER_H

#include "game.h"

#define ANSI_GREEN  "\033[32m"
#define ANSI_RED    "\033[31m"
#define ANSI_YELLOW "\033[33m"
#define ANSI_BLUE   "\033[34m"
#define ANSI_ORANGE "\033[38;5;208m"
#define ANSI_RESET  "\033[0m"


void render_level(Game *game, int key);

#endif