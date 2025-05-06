#include <check.h>
#include "../s21_matrix.h"

START_TEST(mult_matrix_valid_2x2) {
  matrix_t A, B, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1; A.matrix[0][1] = 2;
  A.matrix[1][0] = 3; A.matrix[1][1] = 4;

  B.matrix[0][0] = 2; B.matrix[0][1] = 0;
  B.matrix[1][0] = 1; B.matrix[1][1] = 2;

  expected.matrix[0][0] = 4; expected.matrix[0][1] = 4;
  expected.matrix[1][0] = 10; expected.matrix[1][1] = 8;

  int code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_matrix_incompatible) {
  matrix_t A, B, result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 2, &B);

  int code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(code, INCORRECT_COUNT);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix_null_ptr) {
  matrix_t *A = NULL;
  matrix_t B;
  s21_create_matrix(2, 2, &B);
  matrix_t result;

  int code = s21_mult_matrix(A, &B, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix_null_matrix_field) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  B.matrix = NULL;
  B.rows = 2;
  B.columns = 2;
  matrix_t result;

  int code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_matrix_zero_dimension) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.rows = 0;  // неправильно
  B.columns = 0;

  int code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(code, INCORRECT_COUNT);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *s21_mult_matrix_suite(void) {
  Suite *s = suite_create("s21_mult_matrix");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, mult_matrix_valid_2x2);
  tcase_add_test(tc, mult_matrix_incompatible);
  tcase_add_test(tc, mult_matrix_null_ptr);
  tcase_add_test(tc, mult_matrix_null_matrix_field);
  tcase_add_test(tc, mult_matrix_zero_dimension);

  suite_add_tcase(s, tc);
  return s;
}
