#include <check.h>
#include "../s21_matrix.h"

START_TEST(determinant_1x1) {
  matrix_t A;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 7.0;

  double result = 0.0;
  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq(result, 7.0);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_2x2) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  double result = 0.0;
  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq(result, -2.0);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_3x3) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 6; A.matrix[0][1] = 1; A.matrix[0][2] = 1;
  A.matrix[1][0] = 4; A.matrix[1][1] = -2; A.matrix[1][2] = 5;
  A.matrix[2][0] = 2; A.matrix[2][1] = 8; A.matrix[2][2] = 7;

  double result = 0.0;
  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq(result, -306.0);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_non_square) {
  matrix_t A;
  s21_create_matrix(2, 3, &A);
  double result = 0.0;

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, INCORRECT_COUNT);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_null_matrix) {
  matrix_t *A = NULL;
  double result = 0.0;

  int code = s21_determinant(A, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(determinant_zero_result) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 4;  // Линейно зависимая матрица

  double result = -1.0;
  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq(result, 0.0);

  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_determinant_suite(void) {
  Suite *s = suite_create("s21_determinant");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, determinant_1x1);
  tcase_add_test(tc, determinant_2x2);
  tcase_add_test(tc, determinant_3x3);
  tcase_add_test(tc, determinant_non_square);
  tcase_add_test(tc, determinant_null_matrix);
  tcase_add_test(tc, determinant_zero_result);

  suite_add_tcase(s, tc);
  return s;
}
