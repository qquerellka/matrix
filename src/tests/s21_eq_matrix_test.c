#include <check.h>
// #include <math.h>
#include "../s21_matrix.h"

START_TEST(eq_matrix_equal) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0; A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0; A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 1.0; B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0; B.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_diff_elements) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0;
  B.matrix[0][0] = 1.0000002;  // разница чуть больше допустимой

  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_diff_size) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 3, &B);

  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_null_matrix) {
  matrix_t *A = NULL;
  matrix_t B;
  s21_create_matrix(2, 2, &B);

  ck_assert_int_eq(s21_eq_matrix(A, &B), 0);

  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_null_data) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  free(B.matrix);  // явно обнуляем matrix
  B.matrix = NULL;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);

  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_eq_matrix_suite(void) {
  Suite *s = suite_create("s21_eq_matrix");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, eq_matrix_equal);
  tcase_add_test(tc, eq_matrix_diff_elements);
  tcase_add_test(tc, eq_matrix_diff_size);
  tcase_add_test(tc, eq_matrix_null_matrix);
  tcase_add_test(tc, eq_matrix_null_data);

  suite_add_tcase(s, tc);
  return s;
}
