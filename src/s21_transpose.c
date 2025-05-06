#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (A == NULL || A->matrix == NULL) {
    return INCORRECT_MATRIX;
  }

  if (A->columns <= 0 || A->rows <= 0) {
    return INCORRECT_COUNT;
  }

  s21_create_matrix(A->columns, A->rows, result);

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }
  return OK;
}
