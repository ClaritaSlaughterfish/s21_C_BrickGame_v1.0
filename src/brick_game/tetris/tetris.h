#ifndef TETRIS_H
#define TETRIS_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
  int block_matrix[4][4];
  int x;
  int y;
  int rez;
  int col_line;
  int shag;
  int figura;
  int game_over;
} matrix;

typedef enum {
  Start,     
  Pause,     
  Terminate,  
  Left,       
  Right,
  Up,
  Down,  
  Action  
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;
  
enum FIGURES {LINE, J_SHAPE, L_SHAPE, BLOCK, Z_SHAPE, S_SHAPE, T_SHAPE};

GameInfo_t updateCurrentState(matrix *A, GameInfo_t *game_info);
GameInfo_t init_game(matrix *A);

int userInput(UserAction_t action, bool hold);
void print_stats(GameInfo_t *game_info);
void the_end(GameInfo_t *game_info);
void sigact(UserAction_t action, matrix *A, GameInfo_t *game_info);  //
int choose_figure(matrix *A);
int add_figure_at_screen(matrix *A, GameInfo_t *game_info);
int delete_the_block(matrix *A, GameInfo_t *game_info);
int spawn(matrix *A, GameInfo_t *game_info);
int right(matrix *A, GameInfo_t *game_info);
int left(matrix *A, GameInfo_t *game_info);
int turn(matrix *A, GameInfo_t *game_info);
int add_figure_at_screen(matrix *A, GameInfo_t *game_info);
int remove_line(matrix *A, GameInfo_t *game_info);
int check_continue(matrix A, GameInfo_t game_info);
void free_field(GameInfo_t *game_info);
void print_matrix(GameInfo_t *game_info);

#endif