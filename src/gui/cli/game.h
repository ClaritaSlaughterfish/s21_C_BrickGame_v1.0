#ifndef GAME_H
#define GAME_H
#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../../brick_game/tetris/tetris.h"
void begin_the_game();
void start();
void print_boxes(int top_y, int bottom_y, int left_x, int right_x);
void drow_the_field();
void print_blocks(int x, int y);
void print_stats(GameInfo_t *game_info);
void state_drow(GameInfo_t *game_info);
void game_loop(matrix *A, GameInfo_t *game_info);
void cleanup_resources(GameInfo_t *game_info);
void termination_screen(GameInfo_t *game_info);
#endif
