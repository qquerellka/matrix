#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!A || !A->matrix) {
    return INCORRECT_MATRIX;
  }

  if (A->rows != A->columns) {
    return INCORRECT_COUNT;
  }

  double det = 0.0;
  int code = s21_determinant(A, &det);
  if (code != OK) {
    return code;
  }

  if (fabs(det) < 1e-7) {
    return INCORRECT_MATRIX;
  }

  if (A->rows == 1) {
    code = s21_create_matrix(1, 1, result);
    if (code == OK) {
      result->matrix[0][0] = 1.0 / A->matrix[0][0];
    }
    return code;
  }

  matrix_t complements, transposed;
  code = s21_calc_complements(A, &complements);
  if (code != OK) return code;

  code = s21_transpose(&complements, &transposed);
  s21_remove_matrix(&complements);
  if (code != OK) return code;

  code = s21_create_matrix(A->rows, A->columns, result);
  if (code != OK) {
    s21_remove_matrix(&transposed);
    return code;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = transposed.matrix[i][j] / det;
    }
  }

  s21_remove_matrix(&transposed);
  return OK;
}
