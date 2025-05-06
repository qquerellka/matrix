#include <check.h>
#include "../s21_matrix.h"

START_TEST(transpose_basic_2x3) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &expected);

  A.matrix[0][0] = 1; A.matrix[0][1] = 2; A.matrix[0][2] = 3;
  A.matrix[1][0] = 4; A.matrix[1][1] = 5; A.matrix[1][2] = 6;

  expected.matrix[0][0] = 1; expected.matrix[0][1] = 4;
  expected.matrix[1][0] = 2; expected.matrix[1][1] = 5;
  expected.matrix[2][0] = 3; expected.matrix[2][1] = 6;

  int code = s21_transpose(&A, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_square_2x2) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1; A.matrix[0][1] = 2;
  A.matrix[1][0] = 3; A.matrix[1][1] = 4;

  expected.matrix[0][0] = 1; expected.matrix[0][1] = 3;
  expected.matrix[1][0] = 2; expected.matrix[1][1] = 4;

  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_null_pointer) {
  matrix_t *A = NULL;
  matrix_t result;
  int code = s21_transpose(A, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(transpose_null_matrix_field) {
  matrix_t A;
  A.matrix = NULL;
  A.rows = 2;
  A.columns = 2;
  matrix_t result;

  int code = s21_transpose(&A, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(transpose_invalid_dimensions) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.rows = 0;

  matrix_t result;
  int code = s21_transpose(&A, &result);
  ck_assert_int_eq(code, INCORRECT_COUNT);

  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_transpose_suite(void) {
  Suite *s = suite_create("s21_transpose");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, transpose_basic_2x3);
  tcase_add_test(tc, transpose_square_2x2);
  tcase_add_test(tc, transpose_null_pointer);
  tcase_add_test(tc, transpose_null_matrix_field);
  tcase_add_test(tc, transpose_invalid_dimensions);

  suite_add_tcase(s, tc);
  return s;
}
