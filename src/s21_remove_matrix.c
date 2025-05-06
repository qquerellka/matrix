#include "s21_matrix.h"

void s21_remove_matrix(matrix_t *A) {
  if (A == NULL) {
    return;
  }
  if (A != NULL && A->matrix != NULL) {
    if (A->matrix[0] != NULL) {
      free(A->matrix[0]);  // Сначала освобождаем блок данных
    }
    free(A->matrix);  // Потом массив указателей на строки
    A->matrix = NULL;
  }
  A->rows = 0;
  A->columns = 0;
}