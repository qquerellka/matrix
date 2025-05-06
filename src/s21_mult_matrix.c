#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL) {
    return INCORRECT_MATRIX;
  }

  if (A->columns != B->rows || A->columns <= 0 || B->columns <= 0 ||
      A->rows <= 0 || B->rows <= 0) {
    return INCORRECT_COUNT;
  }

  s21_create_matrix(A->rows, B->columns, result);

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->rows; j++) {
      int sum = 0;
      for (int k = 0; k < A->columns; k++) {
        sum += A->matrix[i][k] * B->matrix[k][j];
      }
      result->matrix[i][j] = sum;
    }
  }
  return OK;
}