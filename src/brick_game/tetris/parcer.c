#include "tetris.h"

int userInput(UserAction_t action, bool hold) {
  action = 0;
  noecho();
  int input = getch();
  hold = true;
  if (input == KEY_UP && hold == true)
    action = Up;
  else if (input == KEY_DOWN)
    action = Down;
  else if (input == KEY_LEFT)
    action = Left;
  else if (input == KEY_RIGHT)
    action = Right;
  else if (input == 27)
    action = Terminate;
  else if (input == KEY_ENTER)
    action = Start;

  else if (input == 32)
    action = Pause;

  return action;
}
void sigact(UserAction_t action, matrix *A, GameInfo_t *game_info) {
  if (game_info->speed < 700) {
    switch (action) {
      case Up:
        turn(A, game_info);
        break;
      case Start:
        updateCurrentState(A, game_info);
        break;
      case Down:
        spawn(A, game_info);
        break;
      case Right:
        right(A, game_info);
        break;
      case Left:
        left(A, game_info);
        break;
      case Terminate:
        A->game_over = 1;
        break;
      case Pause:
        game_info->speed = 2147483647;
        break;

      default:
        break;
    }
  } else {
    switch (action) {
      case Pause:
        updateCurrentState(A, game_info);
        break;

      case Terminate:
        A->game_over = 1;
        break;

      default:
        break;
    }
  }
}
