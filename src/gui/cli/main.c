#include "game.h"

int main() {
  initscr();
  keypad(stdscr, 1);
  noecho();
  curs_set(0);
  matrix A = {0};
  srand(time(NULL));
  A.rez = rand() % 7;
  choose_figure(&A);
  GameInfo_t game_info = init_game(&A);
  A.rez = rand() % 7;
  choose_figure(&A);
  add_figure_at_screen(&A, &game_info);
  game_loop(&A, &game_info);
  cleanup_resources(&game_info);
  return 0;
}
