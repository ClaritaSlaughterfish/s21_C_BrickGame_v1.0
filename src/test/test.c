#include <check.h>

#include "../brick_game/tetris/tetris.h"

START_TEST(tetris_1) {
  matrix A = {0};
  A.rez = 4;
  choose_figure(&A);
  GameInfo_t game_info = init_game(&A);

  add_figure_at_screen(&A, &game_info);

  for (int m = 0; m < 4; m++) {
    for (int k = 0; k < 4; k++) {
      ck_assert_int_eq(A.block_matrix[m][k], game_info.field[m][k + 3]);
    }
  }
  free_field(&game_info);
}
END_TEST

START_TEST(tetris_2) {
  matrix A = {0};
  A.rez = 6;
  choose_figure(&A);
  GameInfo_t game_info = init_game(&A);

  add_figure_at_screen(&A, &game_info);
  sigact(6, &A, &game_info);
  for (int m = 0; m < 4; m++) {
    for (int k = 0; k < 4; k++) {
      ck_assert_int_eq(A.block_matrix[m][k], game_info.field[m + 1][k + 3]);
    }
  }
  free_field(&game_info);
}
END_TEST

START_TEST(tetris_3) {
  matrix A = {0};
  A.rez = 5;
  choose_figure(&A);
  GameInfo_t game_info = init_game(&A);

  add_figure_at_screen(&A, &game_info);
  sigact(4, &A, &game_info);
  for (int m = 0; m < 4; m++) {
    for (int k = 0; k < 4; k++) {
      ck_assert_int_eq(A.block_matrix[m][k], game_info.field[m][k + 4]);
    }
  }
  free_field(&game_info);
}
END_TEST

START_TEST(tetris_8) {
  matrix A = {0};
  A.rez = 5;
  choose_figure(&A);
  GameInfo_t game_info = init_game(&A);

  add_figure_at_screen(&A, &game_info);
  int x = 0;
  while (x < 3) {
    sigact(5, &A, &game_info);
    sigact(4, &A, &game_info);
    x++;
  }
  sigact(5, &A, &game_info);
  sigact(5, &A, &game_info);
  for (int m = 0; m < 4; m++) {
    for (int k = 0; k < 4; k++) {
      ck_assert_int_eq(A.block_matrix[m][k], game_info.field[m][k + 6]);
    }
  }
  free_field(&game_info);
}
END_TEST

START_TEST(tetris_4) {
  matrix A = {0};
  A.rez = 3;
  choose_figure(&A);
  GameInfo_t game_info = init_game(&A);

  add_figure_at_screen(&A, &game_info);
  sigact(3, &A, &game_info);
  for (int m = 0; m < 4; m++) {
    for (int k = 0; k < 4; k++) {
      ck_assert_int_eq(A.block_matrix[m][k], game_info.field[m][k + 2]);
    }
  }
  sigact(2, &A, &game_info);
  ck_assert_int_eq(A.game_over, 1);
  free_field(&game_info);
}
END_TEST

START_TEST(tetris_5) {
  matrix A = {0};
  A.rez = 2;
  choose_figure(&A);
  GameInfo_t game_info = init_game(&A);

  add_figure_at_screen(&A, &game_info);
  sigact(1, &A, &game_info);
  sigact(10, &A, &game_info);
  sigact(2, &A, &game_info);
  ck_assert_int_eq(A.game_over, 1);
  ck_assert_int_eq(game_info.speed, 2147483647);
  sigact(1, &A, &game_info);
  ck_assert_int_eq(game_info.speed, 600);
  free_field(&game_info);
}
END_TEST

START_TEST(tetris_6) {
  matrix A = {0};

  A.rez = 0;
  choose_figure(&A);
  GameInfo_t game_info = init_game(&A);
  add_figure_at_screen(&A, &game_info);
  int x = 0;
  sigact(0, &A, &game_info);
  sigact(10, &A, &game_info);

  x = 0;
  while (x < 20) {
    sigact(6, &A, &game_info);
    x++;
  }

  x = 0;
  A.rez = 1;
  choose_figure(&A);
  add_figure_at_screen(&A, &game_info);

  while (x < 4) {
    sigact(3, &A, &game_info);
    x++;
  }
  x = 0;
  add_figure_at_screen(&A, &game_info);

  while (x < 20) {
    sigact(6, &A, &game_info);
    x++;
  }

  x = 0;
  A.rez = 2;
  choose_figure(&A);
  add_figure_at_screen(&A, &game_info);

  while (x < 4) {
    sigact(4, &A, &game_info);
    x++;
  }
  x = 0;
  while (x < 21) {
    sigact(6, &A, &game_info);

    x++;
  }

  for (int m = 1; m < 9; m++) {
    ck_assert_int_eq(game_info.field[21][m], 0);
  }
  free_field(&game_info);
}
END_TEST

START_TEST(tetris_7) {
  matrix A = {0};
  A.rez = 4;
  choose_figure(&A);
  GameInfo_t game_info = init_game(&A);
  add_figure_at_screen(&A, &game_info);

  sigact(0, &A, &game_info);
  sigact(5, &A, &game_info);

  for (int m = 0; m < 4; m++) {
    for (int k = 0; k < 4; k++) {
      ck_assert_int_eq(A.block_matrix[m][k], game_info.field[m][k + 3]);
    }
  }

  free_field(&game_info);
}
END_TEST

int main() {
  Suite *s1 = suite_create("Core");
  TCase *tc_core = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;
  suite_add_tcase(s1, tc_core);

  tcase_add_test(tc_core, tetris_1);
  tcase_add_test(tc_core, tetris_2);
  tcase_add_test(tc_core, tetris_3);
  tcase_add_test(tc_core, tetris_4);
  tcase_add_test(tc_core, tetris_5);
  tcase_add_test(tc_core, tetris_6);
  tcase_add_test(tc_core, tetris_7);
  tcase_add_test(tc_core, tetris_8);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
