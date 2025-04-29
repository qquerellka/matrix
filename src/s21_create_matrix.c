#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows <= 0 || columns <= 0 || result == NULL) {
    return INCORRECT_MATRIX;
  }

  result->rows = rows;
  result->columns = columns;

  // Выделяем память под массив указателей + под данные
  result->matrix = (double **)malloc(rows * sizeof(double *));
  if (result->matrix == NULL) return INCORRECT_MATRIX;

  double *data = (double *)calloc(rows * columns, sizeof(double));
  if (data == NULL) {
    free(result->matrix);
    result->matrix = NULL;
    return INCORRECT_MATRIX;
  }

  // Привязываем строки к нужным позициям в общем блоке
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = data + i * columns;
  }

  return OK;
}
