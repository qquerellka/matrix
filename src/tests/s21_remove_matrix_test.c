#include <check.h>
#include "../s21_matrix.h"

START_TEST(remove_matrix_valid) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  // Убедимся, что память действительно выделена
  ck_assert_ptr_nonnull(A.matrix);
  ck_assert_ptr_nonnull(A.matrix[0]);

  s21_remove_matrix(&A);

  // После удаления должно быть NULL и 0 размер
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(remove_matrix_null_input) {
  matrix_t *A = NULL;
  // Функция не должна упасть
  s21_remove_matrix(A);
  ck_assert_ptr_null(A);  // Просто убеждаемся, что ничего не сломалось
}
END_TEST

START_TEST(remove_matrix_already_null) {
  matrix_t A;
  A.matrix = NULL;
  A.rows = 10;
  A.columns = 10;

  s21_remove_matrix(&A);

  // Всё должно быть обнулено
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

Suite *s21_remove_matrix_suite(void) {
  Suite *s = suite_create("s21_remove_matrix");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, remove_matrix_valid);
  tcase_add_test(tc, remove_matrix_null_input);
  tcase_add_test(tc, remove_matrix_already_null);

  suite_add_tcase(s, tc);
  return s;
}
