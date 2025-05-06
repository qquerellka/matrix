#include <check.h>
#include "../s21_matrix.h"

START_TEST(inverse_matrix_2x2) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 4; A.matrix[0][1] = 7;
  A.matrix[1][0] = 2; A.matrix[1][1] = 6;

  expected.matrix[0][0] = 0.6;   expected.matrix[0][1] = -0.7;
  expected.matrix[1][0] = -0.2;  expected.matrix[1][1] = 0.4;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_1x1) {
  matrix_t A, result;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 4;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.25, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_non_square) {
  matrix_t A, result;
  s21_create_matrix(2, 3, &A);

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, INCORRECT_COUNT);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_null) {
  matrix_t *A = NULL;
  matrix_t result;

  int code = s21_inverse_matrix(A, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(inverse_matrix_singular) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 4;  // линейно зависимые строки, det = 0

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_invalid_dimensions) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.rows = 0;

  matrix_t result;
  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, INCORRECT_COUNT);

  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_inverse_matrix_suite(void) {
  Suite *s = suite_create("s21_inverse_matrix");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, inverse_matrix_2x2);
  tcase_add_test(tc, inverse_matrix_1x1);
  tcase_add_test(tc, inverse_matrix_non_square);
  tcase_add_test(tc, inverse_matrix_null);
  tcase_add_test(tc, inverse_matrix_singular);
  tcase_add_test(tc, inverse_matrix_invalid_dimensions);

  suite_add_tcase(s, tc);
  return s;
}
