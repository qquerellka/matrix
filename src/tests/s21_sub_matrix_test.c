#include <check.h>
#include "../s21_matrix.h"

START_TEST(sub_matrix_valid) {
  matrix_t A, B, result, expected;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 5.0; A.matrix[0][1] = 4.0;
  A.matrix[1][0] = 3.0; A.matrix[1][1] = 2.0;

  B.matrix[0][0] = 1.0; B.matrix[0][1] = 1.0;
  B.matrix[1][0] = 1.0; B.matrix[1][1] = 1.0;

  expected.matrix[0][0] = 4.0; expected.matrix[0][1] = 3.0;
  expected.matrix[1][0] = 2.0; expected.matrix[1][1] = 1.0;

  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(sub_matrix_diff_size) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 2, &B);

  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, INCORRECT_COUNT);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix_null_ptr) {
  matrix_t *A = NULL;
  matrix_t B;
  s21_create_matrix(2, 2, &B);
  matrix_t result;

  int code = s21_sub_matrix(A, &B, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix_null_matrix_field) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  B.matrix = NULL;
  B.rows = 2;
  B.columns = 2;
  matrix_t result;

  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(sub_matrix_zero_size) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.rows = 0;  // некорректный размер
  B.columns = 0;

  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, INCORRECT_COUNT);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *s21_sub_matrix_suite(void) {
  Suite *s = suite_create("s21_sub_matrix");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, sub_matrix_valid);
  tcase_add_test(tc, sub_matrix_diff_size);
  tcase_add_test(tc, sub_matrix_null_ptr);
  tcase_add_test(tc, sub_matrix_null_matrix_field);
  tcase_add_test(tc, sub_matrix_zero_size);

  suite_add_tcase(s, tc);
  return s;
}
