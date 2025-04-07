#include <CUnit/Basic.h>
#include <stdlib.h>
#include <stdio.h>
#include "../src/main.h"  // подключаем main.c для тестирования
#include "tests_main.h"

// Тест на успешную загрузку матриц и выполнение вычислений
void test_main_success() {
    // Здесь можно смоделировать ситуацию, когда все файлы существуют и корректно загружаются
    CU_ASSERT_EQUAL(main_project(), 0);  // Ожидаем код возврата 0 при успешной загрузке и вычислениях
}

// Тест на ошибку при отсутствии одного файла (например, файла A.txt)
void test_main_failure() {
    // Сместим путь к одному из файлов или сделаем его недоступным
    // Можно создать тестовые матрицы и удалить их перед тестом.
    // Пример: удалим файл "matrix_data_for_the_program/A.txt"
    remove("matrix_data_for_the_program/A.txt");

    CU_ASSERT_EQUAL(main_project(), 1);  // Ожидаем код возврата 1 при ошибке загрузки
}

int main_tests_main() {
    CU_pSuite pSuiteMain = CU_add_suite("Main Tests", NULL, NULL);
    if (pSuiteMain == NULL) {
        return CU_get_error();
    }

    // Добавляем тесты в suite
    if (CU_add_test(pSuiteMain, "Test Success Case", test_main_success) == NULL ||
        CU_add_test(pSuiteMain, "Test Failure Case", test_main_failure) == NULL) {
        return CU_get_error();
    }

    printf("Все тесты пройдены успешно!\n");

    return 0;
}