#include "s21_matrix.h"


int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (A == NULL || A->matrix == NULL) {
    return INCORRECT_MATRIX;
  }

  int code = s21_create_matrix(A->rows, A->columns, result);
  if (code != OK) {
    return code;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return OK;
}