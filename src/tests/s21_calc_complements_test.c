#include "../s21_matrix.h"
#include <check.h>

START_TEST(calc_complements_2x2) {
  matrix_t A, expected, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  // Алгебраические дополнения:
  expected.matrix[0][0] = 4;
  expected.matrix[0][1] = -3;
  expected.matrix[1][0] = -2;
  expected.matrix[1][1] = 1;

  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_1x1) {
  matrix_t A, result;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5;

  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  ck_assert_double_eq(result.matrix[0][0], 1.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_not_square) {
  matrix_t A;
  s21_create_matrix(2, 3, &A);
  matrix_t result;
  int code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(code, INCORRECT_COUNT);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_null) {
  matrix_t *A = NULL;
  matrix_t result;
  int code = s21_calc_complements(A, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(calc_complements_create_matrix_fail) {
  // Передаём матрицу 0x0
  matrix_t A;
  s21_create_matrix(0, 0, &A); // или вручную обнуляем A
  matrix_t result;
  int code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(code, INCORRECT_COUNT); // или INCORRECT_MATRIX
}
END_TEST

Suite *s21_calc_complements_suite(void) {
  Suite *s = suite_create("s21_calc_complements");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, calc_complements_2x2);
  tcase_add_test(tc, calc_complements_1x1);
  tcase_add_test(tc, calc_complements_not_square);
  tcase_add_test(tc, calc_complements_null);
  tcase_add_test(tc, calc_complements_create_matrix_fail);

  suite_add_tcase(s, tc);
  return s;
}
