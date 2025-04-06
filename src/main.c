#include <stdio.h>
#include <stdlib.h>
#include "matrix/matrix.h"
#include "output/output.h"
#include "main.h"

int main() {
    //A−B×C+DT - это мой пример, вариант 5.
    int return_value = 0;


    // Загружаем матрицы из файлов
    Matrix* A = load_matrix_from_file("matrix_data_for_the_program/A.txt");
    Matrix* B = load_matrix_from_file("matrix_data_for_the_program/B.txt");
    Matrix* C = load_matrix_from_file("matrix_data_for_the_program/C.txt");
    Matrix* D = load_matrix_from_file("matrix_data_for_the_program/D.txt");

    // Проверка на успешную загрузку
    if (A == NULL) {
        printf("Ошибка: не удалось загрузить матрицу A\n"); 
        return_value = 1;
    }
    if (B == NULL) {
        printf("Ошибка: не удалось загрузить матрицу B\n"); 
        return_value = 1;
    }
    if (C == NULL) {
        printf("Ошибка: не удалось загрузить матрицу C\n"); 
        return_value = 1;
    }
    if (D == NULL) {
        printf("Ошибка: не удалось загрузить матрицу D\n"); 
        return_value = 1;
    }

    // 1. Вычисляем B * C
    Matrix* BC = multiply_matrices(B, C);
    if (BC == NULL) {
        printf("Ошибка: не удалось выполнить умножение матриц B и C\n"); 
        return_value = 1;
    }

    // 2. Транспонируем D
    Matrix* DT = transpose_matrix(D);
    if (DT == NULL) {
        printf("Ошибка: не удалось транспонировать матрицу D\n"); 
        return_value = 1;
    }
    
    // 3. Вычисляем A - (B * C) + D^T
    Matrix* result1 = add_matrices(A, DT);
    if (result1 == NULL) {
        printf("Ошибка: не удалось выполнить сложение A и D^T\n"); 
        return_value = 1;
    }

    Matrix* result = add_matrices(result1, BC);
    if (result == NULL) {
        printf("Ошибка: не удалось выполнить сложение A - B * C + D^T\n"); 
        return_value = 1;
    }

    // 4. Выводим результат
    printf("Результат выражения A - B * C + D^T:\n");
    print_matrix(result);

    // Освобождаем память
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
    free_matrix(D);
    free_matrix(BC);
    free_matrix(DT);
    free_matrix(result1);
    free_matrix(result);

    return return_value;
}
