#include <check.h>
#include <stdlib.h>

// Объявления всех функций, создающих тестовые случаи
Suite *s21_create_matrix_suite(void);
Suite *s21_remove_matrix_suite(void);
Suite *s21_eq_matrix_suite(void);
Suite *s21_sum_matrix_suite(void);
Suite *s21_sub_matrix_suite(void);
Suite *s21_mult_matrix_suite(void);
Suite *s21_mult_number_suite(void);
Suite *s21_transpose_suite(void);
Suite *s21_calc_complements_suite(void);
Suite *s21_determinant_suite(void);
Suite *s21_inverse_matrix_suite(void);

int main(void) {
  int failed = 0;
  SRunner *sr = srunner_create(s21_create_matrix_suite());
  srunner_add_suite(sr, s21_remove_matrix_suite());
  srunner_add_suite(sr, s21_eq_matrix_suite());
  srunner_add_suite(sr, s21_sum_matrix_suite());
  srunner_add_suite(sr, s21_sub_matrix_suite());
  srunner_add_suite(sr, s21_mult_matrix_suite());
  srunner_add_suite(sr, s21_mult_number_suite());
  srunner_add_suite(sr, s21_transpose_suite());
  srunner_add_suite(sr, s21_calc_complements_suite());
  srunner_add_suite(sr, s21_determinant_suite());
  srunner_add_suite(sr, s21_inverse_matrix_suite());

  srunner_run_all(sr, CK_VERBOSE);
  failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
