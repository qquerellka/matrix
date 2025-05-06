#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  if (A == NULL || A->matrix == NULL) {
    return INCORRECT_MATRIX;
  }
  if (A->columns != A->rows || A->columns <= 0 || A->rows <= 0) {
    return INCORRECT_COUNT;
  }

  if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else {
    if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      double det = 0.0;

      for (int col = 0; col < A->rows; col++) {
        matrix_t minor;
        s21_create_matrix(A->rows - 1, A->rows - 1, &minor);
        // if (code != OK) {
        //   return code;
        // }

        // Формируем минор (без строки 0 и столбца col)
        for (int i = 1; i < A->rows; i++) {
          int minor_col = 0;
          for (int j = 0; j < A->rows; j++) {
            if (j != col) {
              minor.matrix[i - 1][minor_col] = A->matrix[i][j];
              minor_col++;
            }
          }
        }

        double minor_det = 0.0;
        s21_determinant(&minor, &minor_det);
        det += pow(-1, col) * A->matrix[0][col] * minor_det;

        s21_remove_matrix(&minor);
      }
      *result = det;
    }
  }
  return OK;
}