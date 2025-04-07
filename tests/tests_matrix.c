#include <CUnit/Basic.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "../src/main.h"  // подключаем main.c для тестирования
#include "../src/matrix/matrix.h"
#include "tests_matrix.h"

// Тест для создания матрицы
void test_create_matrix() {
    Matrix* matrix = create_matrix(3, 3);
    assert(matrix != NULL && "Ошибка: матрица не создана");
    assert(matrix->rows == 3 && matrix->cols == 3 && "Ошибка: неверные размеры матрицы");
    free_matrix(matrix);
}

// Тест для освобождения памяти
void test_free_matrix() {
    Matrix* matrix = create_matrix(2, 2);
    assert(matrix != NULL && "Ошибка: матрица не создана");
    free_matrix(matrix);  // Просто проверяем, что освобождение памяти не вызывает проблем
}

// Тест для копирования матрицы
void test_copy_matrix() {
    Matrix* original = create_matrix(2, 2);
    original->data[0][0] = 1.0;
    original->data[0][1] = 2.0;
    original->data[1][0] = 3.0;
    original->data[1][1] = 4.0;

    Matrix* copy = copy_matrix(original);
    assert(copy != NULL && "Ошибка: копия матрицы не была создана");
    assert(copy->data[0][0] == 1.0 && "Ошибка: неверное значение в копии матрицы");
    assert(copy->data[0][1] == 2.0 && "Ошибка: неверное значение в копии матрицы");
    assert(copy->data[1][0] == 3.0 && "Ошибка: неверное значение в копии матрицы");
    assert(copy->data[1][1] == 4.0 && "Ошибка: неверное значение в копии матрицы");

    free_matrix(original);
    free_matrix(copy);
}

// Тест для сложения матриц
void test_add_matrices() {
    Matrix* A = create_matrix(2, 2);
    Matrix* B = create_matrix(2, 2);

    A->data[0][0] = 1.0;
    A->data[0][1] = 2.0;
    A->data[1][0] = 3.0;
    A->data[1][1] = 4.0;

    B->data[0][0] = 5.0;
    B->data[0][1] = 6.0;
    B->data[1][0] = 7.0;
    B->data[1][1] = 8.0;

    Matrix* result = add_matrices(A, B);
    assert(result != NULL && "Ошибка: результат сложения матриц - NULL");
    assert(result->data[0][0] == 6.0 && "Ошибка: неверный результат сложения");
    assert(result->data[0][1] == 8.0 && "Ошибка: неверный результат сложения");
    assert(result->data[1][0] == 10.0 && "Ошибка: неверный результат сложения");
    assert(result->data[1][1] == 12.0 && "Ошибка: неверный результат сложения");

    free_matrix(A);
    free_matrix(B);
    free_matrix(result);
}

// Тест для умножения матриц
void test_multiply_matrices() {
    Matrix* A = create_matrix(2, 3);
    Matrix* B = create_matrix(3, 2);

    A->data[0][0] = 1.0;
    A->data[0][1] = 2.0;
    A->data[0][2] = 3.0;
    A->data[1][0] = 4.0;
    A->data[1][1] = 5.0;
    A->data[1][2] = 6.0;

    B->data[0][0] = 7.0;
    B->data[0][1] = 8.0;
    B->data[1][0] = 9.0;
    B->data[1][1] = 10.0;
    B->data[2][0] = 11.0;
    B->data[2][1] = 12.0;

    Matrix* result = multiply_matrices(A, B);
    assert(result != NULL && "Ошибка: результат умножения матриц - NULL");
    assert(result->data[0][0] == 58.0 && "Ошибка: неверный результат умножения");
    assert(result->data[0][1] == 64.0 && "Ошибка: неверный результат умножения");
    assert(result->data[1][0] == 139.0 && "Ошибка: неверный результат умножения");
    assert(result->data[1][1] == 154.0 && "Ошибка: неверный результат умножения");

    free_matrix(A);
    free_matrix(B);
    free_matrix(result);
}

// Тест для транспонирования матрицы
void test_transpose_matrix() {
    Matrix* A = create_matrix(2, 3);
    A->data[0][0] = 1.0;
    A->data[0][1] = 2.0;
    A->data[0][2] = 3.0;
    A->data[1][0] = 4.0;
    A->data[1][1] = 5.0;
    A->data[1][2] = 6.0;

    Matrix* result = transpose_matrix(A);
    assert(result != NULL && "Ошибка: результат транспонирования - NULL");
    assert(result->data[0][0] == 1.0 && "Ошибка: неверное значение при транспонировании");
    assert(result->data[0][1] == 4.0 && "Ошибка: неверное значение при транспонировании");
    assert(result->data[1][0] == 2.0 && "Ошибка: неверное значение при транспонировании");
    assert(result->data[1][1] == 5.0 && "Ошибка: неверное значение при транспонировании");
    assert(result->data[2][0] == 3.0 && "Ошибка: неверное значение при транспонировании");
    assert(result->data[2][1] == 6.0 && "Ошибка: неверное значение при транспонировании");

    free_matrix(A);
    free_matrix(result);
}

// Тест для вычисления детерминанта
void test_determinant() {
    Matrix* A = create_matrix(2, 2);
    A->data[0][0] = 1.0;
    A->data[0][1] = 2.0;
    A->data[1][0] = 3.0;
    A->data[1][1] = 4.0;

    MATRIX_TYPE det = determinant(A);
    assert(det == -2.0 && "Ошибка: неверное значение детерминанта");

    free_matrix(A);
}

int main_tests_matrix() {
    // Запуск тестов
    test_create_matrix();
    test_free_matrix();
    test_copy_matrix();
    test_add_matrices();
    test_multiply_matrices();
    test_transpose_matrix();
    test_determinant();

    printf("Все тесты пройдены успешно!\n");

    return 0;
}
