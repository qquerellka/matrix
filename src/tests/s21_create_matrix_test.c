#include <check.h>
#include "../s21_matrix.h"

START_TEST(create_matrix_valid) {
  matrix_t A;
  int code = s21_create_matrix(3, 3, &A);

  ck_assert_int_eq(code, OK);
  ck_assert_ptr_nonnull(A.matrix);
  ck_assert_int_eq(A.rows, 3);
  ck_assert_int_eq(A.columns, 3);

  // Проверим, что память действительно выделена
  for (int i = 0; i < A.rows; i++) {
    ck_assert_ptr_nonnull(A.matrix[i]);
  }

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_matrix_zero_rows) {
  matrix_t A;
  int code = s21_create_matrix(0, 3, &A);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(create_matrix_zero_columns) {
  matrix_t A;
  int code = s21_create_matrix(3, 0, &A);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(create_matrix_negative_size) {
  matrix_t A;
  int code = s21_create_matrix(-5, -5, &A);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(create_matrix_null_result) {
  int code = s21_create_matrix(3, 3, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

Suite *s21_create_matrix_suite(void) {
  Suite *s = suite_create("s21_create_matrix");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, create_matrix_valid);
  tcase_add_test(tc, create_matrix_zero_rows);
  tcase_add_test(tc, create_matrix_zero_columns);
  tcase_add_test(tc, create_matrix_negative_size);
  tcase_add_test(tc, create_matrix_null_result);

  suite_add_tcase(s, tc);
  return s;
}
