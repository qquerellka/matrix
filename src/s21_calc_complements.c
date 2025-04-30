#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (!A || !A->matrix) {
    return INCORRECT_MATRIX;
  }

  if (A->rows != A->columns) {
    return INCORRECT_COUNT;
  }

  int size = A->rows;
  int code = s21_create_matrix(size, size, result);
  if (code != OK) {
    return code;
  }
  if (size == 1) {
    result->matrix[0][0] = 1.0;
  } else {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        matrix_t minor;
        code = s21_create_matrix(size - 1, size - 1, &minor);
        if (code != OK) {
          s21_remove_matrix(result);
          return code;
        }

        int row_m = 0;
        for (int r = 0; r < size; r++) {
          if (r != i) {
            int col_m = 0;
            for (int c = 0; c < size; c++) {
              if (c != j) {
              minor.matrix[row_m][col_m++] = A->matrix[r][c];
              }
            }
            row_m++;
          }
        }
        double det = 0.0;
        s21_determinant(&minor, &det);
        int sign = ((i + j) % 2 == 0) ? 1 : -1;
        result->matrix[i][j] = sign * det;
        s21_remove_matrix(&minor);
      }
    }
  }
  return OK;
}
