#pragma once


/**
 * @file output.h
 * @brief Заголовочный файл для функций вывода и сохранения матрицы
 * 
 * Этот файл объявляет функции для вывода матрицы в консоль и её сохранения в файл.
 * Он предоставляет интерфейсы для отладки и сохранения результатов работы с матрицами.
 * 
 * Включает функции:
 * - `print_matrix` — выводит матрицу в консоль.
 * - `save_matrix_to_file` — сохраняет матрицу в текстовый файл.
 * 
 * @see output.c
 */



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