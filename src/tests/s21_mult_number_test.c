#include <check.h>
#include "../s21_matrix.h"

START_TEST(mult_number_basic) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1.0; A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0; A.matrix[1][1] = 4.0;

  double num = 2.0;

  expected.matrix[0][0] = 2.0; expected.matrix[0][1] = 4.0;
  expected.matrix[1][0] = 6.0; expected.matrix[1][1] = 8.0;

  ck_assert_int_eq(s21_mult_number(&A, num, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_number_zero) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = -1.0; A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.5;  A.matrix[1][1] = -4.5;

  double num = 0.0;

  expected.matrix[0][0] = 0.0; expected.matrix[0][1] = 0.0;
  expected.matrix[1][0] = 0.0; expected.matrix[1][1] = 0.0;

  ck_assert_int_eq(s21_mult_number(&A, num, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_number_negative_scalar) {
  matrix_t A, result;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 10.0;

  double num = -3.0;

  ck_assert_int_eq(s21_mult_number(&A, num, &result), OK);
  ck_assert_double_eq(result.matrix[0][0], -30.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_number_null_matrix) {
  matrix_t *A = NULL;
  matrix_t result;
  ck_assert_int_eq(s21_mult_number(A, 5.0, &result), INCORRECT_MATRIX);
}
END_TEST

START_TEST(mult_number_bad_dimensions) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);
  A.rows = 0;
  A.columns = -1;
  ck_assert_int_eq(s21_mult_number(&A, 3.0, &result), INCORRECT_COUNT);
  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_mult_number_suite(void) {
  Suite *s = suite_create("s21_mult_number");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, mult_number_basic);
  tcase_add_test(tc, mult_number_zero);
  tcase_add_test(tc, mult_number_negative_scalar);
  tcase_add_test(tc, mult_number_null_matrix);
  tcase_add_test(tc, mult_number_bad_dimensions);

  suite_add_tcase(s, tc);
  return s;
}
