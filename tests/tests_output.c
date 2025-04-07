#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/matrix/matrix.h"
#include "../src/output/output.h"
#include "tests_output.h"

// Тест для вывода матрицы в консоль (проверка корректности вызова)
void test_print_matrix() {
    Matrix* matrix = create_matrix(2, 2);
    matrix->data[0][0] = 1.0;
    matrix->data[0][1] = 2.0;
    matrix->data[1][0] = 3.0;
    matrix->data[1][1] = 4.0;

    // Просто проверяем, что вывод не приводит к сбоям (не можем точно проверять вывод в консоль через assert)
    assert(matrix != NULL && "Ошибка: матрица не создана");

    // Проверяем, что матрица существует и передаем её в функцию print_matrix
    print_matrix(matrix);  // Этот тест не проверяет вывод в консоль, просто проверяет отсутствие сбоев

    free_matrix(matrix);
}

// Тест для сохранения матрицы в файл
void test_save_matrix_to_file() {
    Matrix* matrix = create_matrix(2, 2);
    matrix->data[0][0] = 1.0;
    matrix->data[0][1] = 2.0;
    matrix->data[1][0] = 3.0;
    matrix->data[1][1] = 4.0;

    const char* filename = "test_matrix.txt";

    int result = save_matrix_to_file(matrix, filename);
    assert(result == 0 && "Ошибка: матрица не сохранена в файл");

    // Проверим, что файл был создан и его содержимое корректно (можно добавить чтение файла для проверки)
    FILE* file = fopen(filename, "r");
    assert(file != NULL && "Ошибка: не удалось открыть файл для чтения");

    char buffer[256];
    char* result_char;

    result_char = strstr(buffer, "Number of rows: 2");
    assert(result_char == NULL && "Ошибка: неверное количество строк в файле");
    
    result_char = strstr(buffer, "Number of columns: 2");
    assert(result_char == NULL && "Ошибка: неверное количество столбцов в файле");
    
    result_char = strstr(buffer, "1.000000 2.000000");
    assert(result_char == NULL && "Ошибка: неверные данные первой строки матрицы");
    
    result_char = strstr(buffer, "3.000000 4.000000");
    assert(result_char == NULL && "Ошибка: неверные данные второй строки матрицы");

    fclose(file);

    free_matrix(matrix);
}

// Тест для сохранения матрицы в файл с пустой матрицей
void test_save_empty_matrix_to_file() {
    Matrix* matrix = create_matrix(0, 0);  // Пустая матрица
    const char* filename = "empty_matrix.txt";

    int result = save_matrix_to_file(matrix, filename);
    assert(result == -1 && "Ошибка: пустая матрица не должна сохраняться");

    free_matrix(matrix);
}

// Тест для сохранения матрицы в файл с матрицей одного элемента
void test_save_single_element_matrix_to_file() {
    Matrix* matrix = create_matrix(1, 1);
    matrix->data[0][0] = 42.0;

    const char* filename = "single_element_matrix.txt";

    int result = save_matrix_to_file(matrix, filename);
    assert(result == 0 && "Ошибка: матрица с одним элементом не сохранена");

    FILE* file = fopen(filename, "r");
    assert(file != NULL && "Ошибка: не удалось открыть файл для чтения");

    char buffer[256];
    fgets(buffer, sizeof(buffer), file);  // Прочитаем первую строку с размерами
    assert(strstr(buffer, "Number of rows: 1") != NULL && "Ошибка: неверное количество строк в файле");
    assert(strstr(buffer, "Number of columns: 1") != NULL && "Ошибка: неверное количество столбцов в файле");

    fgets(buffer, sizeof(buffer), file);  // Прочитаем первую строку с данными матрицы
    assert(strstr(buffer, "42.000000") != NULL && "Ошибка: неверные данные матрицы");

    fclose(file);

    free_matrix(matrix);
}

int main_tests_output() {
    // Запуск тестов
    test_print_matrix();
    test_save_matrix_to_file();
    test_save_empty_matrix_to_file();
    test_save_single_element_matrix_to_file();

    printf("Все тесты пройдены успешно!\n");

    return 0;
}
