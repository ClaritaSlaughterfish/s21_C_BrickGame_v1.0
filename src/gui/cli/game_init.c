#include "game.h"
void drow_the_field() {
  print_boxes(0, 21, 0, 21);
  print_boxes(17, 21, 26, 35);
  print_boxes(1, 3, 26, 26 + 12);
  print_boxes(4, 6, 26, 26 + 12);
  print_boxes(7, 9, 26, 26 + 12);
  print_boxes(10, 12, 26, 26 + 12);

  mvprintw(2, 27, "LEVEL");
  mvprintw(5, 27, "SCORE");
  mvprintw(8, 27, "SPEED");
  mvprintw(11, 27, "BEST");
  mvprintw(16, 27, "NEXT");
}

void print_boxes(int top_y, int bottom_y, int left_x, int right_x) {
  mvaddch(top_y, left_x, ACS_ULCORNER);
  int i = left_x + 1;

  for (; i < right_x; i++) mvaddch(top_y, i, ACS_HLINE);
  mvaddch(top_y, i, ACS_URCORNER);

  for (int i = top_y + 1; i < bottom_y; i++) {
    mvaddch(i, left_x, ACS_VLINE);
    mvaddch(i, right_x, ACS_VLINE);
  }

  mvaddch(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++) mvaddch(bottom_y, i, ACS_HLINE);
  mvaddch(bottom_y, i, ACS_LRCORNER);
}

void print_blocks(int x, int y) {
    initscr(); 
    start_color(); 
    init_pair(1, COLOR_WHITE, COLOR_BLACK); 
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    attron(COLOR_PAIR(1)); 
    mvaddch(x, 1 + y * 2, ' ' | A_REVERSE); 
    mvaddch(x, 2 + y * 2, ' ' | A_REVERSE); 
    attroff(COLOR_PAIR(1)); 
}


void start() {
  mvprintw(5, 16, "welcome to");
  mvprintw(6, 18, "TETRIS");
  mvprintw(7, 16, "by claritas");
  mvprintw(9, 15, "press any key");

  mvprintw(15, 15, "CONTROL BUTTONS:");
  mvprintw(16, 11, "ARROWS - move and rotate");
  mvprintw(17, 16, "SPACE - pause");
  mvprintw(18, 17, "ESC - leave");


  getch();
}
void print_stats(GameInfo_t *game_info) {
  mvprintw(2, 27 + 6, "%d", game_info->level);
  mvprintw(5, 33, "%d", game_info->score);
  if (game_info->speed > 600) {
    mvprintw(6, 7, "PAUSE");
    mvprintw(8, 6, "press space");
    mvprintw(10, 6, "to continue");
  } else {
    mvprintw(8, 33, "%d", (600 - game_info->speed) / 40);
  }
  mvprintw(11, 33, "%d", game_info->high_score);
}
void termination_screen(GameInfo_t *game_info) {
  if (game_info->score > game_info->high_score) {
    mvprintw(7, 16, "NEW BEST SCORE %d", game_info->score);
    FILE *file;
    if ((file = fopen("the_best_score.txt", "w")) != NULL) {
      fprintf(file, "%d", game_info->score);
    }
  } else mvprintw(10, 16, "YOUR SCORE  %d", game_info->score);
}
void state_drow(GameInfo_t *game_info) {
  drow_the_field();
  print_stats(game_info);
  for (int i = 2; i < 22; i++) {
    for (int j = 0; j < 10; j++) {
      if (game_info->field[i][j] == 1) {
        print_blocks(i - 1, j);
      }
    }
  }
  for (int k = 0; k < 4; k++) {
    for (int m = 0; m < 4; m++) {
      if (game_info->next[k][m] == 1) {
        print_blocks(k + 18, m + 13);
      }
    }
  }
}
