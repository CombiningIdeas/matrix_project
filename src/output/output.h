#pragma once

#include "../matrix/matrix.h"
#include "../../include/config.h"


/**
 * @brief Выводит матрицу в консоль
 * @param matrix Указатель на матрицу
 */
void print_matrix(const Matrix* matrix);


/**
 * @brief Сохраняет матрицу в текстовый файл
 * @param matrix Указатель на матрицу
 * @param filename Имя файла
 * @return 0 в случае успеха, -1 в случае ошибки
 */
int save_matrix_to_file(const Matrix* matrix, const char* filename);