#include <CUnit/Basic.h>
#include "tests_matrix.h"
#include "tests_output.h"
#include "tests_main.h"  



/**
 * @file test_runner.c
 * @brief Основной файл для запуска всех тестов в проекте.
 * 
 * Этот файл содержит основной код для запуска всех тестов в проекте.
 * Он инициализирует систему тестирования CUnit, добавляет тесты, 
 * запускает их и выводит результаты.
 * 
 * В этом файле вызываются тесты для работы с матрицами, вывода и main.c.
 */



/**
 * @brief Главная функция для инициализации и запуска всех тестов.
 * 
 * Эта функция инициализирует систему CUnit, добавляет тесты для разных
 * компонентов программы, запускает их и выводит результаты. В случае
 * ошибок в тестах выводится сообщение с кодом ошибки.
 * 
 * @details
 * Функция выполняет следующие действия:
 * 1. Инициализирует реестр CUnit с помощью `CU_initialize_registry()`.
 * 2. Добавляет наборы тестов для матриц, вывода и основного кода с помощью `CU_add_suite()`.
 * 3. Запускает тесты для каждой категории:
 *    - Тесты матриц
 *    - Тесты вывода
 *    - Тесты main.c
 * 4. Выводит ошибки, если они возникают при выполнении тестов.
 * 5. Настроены различные уровни вывода:
 *    - Подробный вывод (`CU_BRM_VERBOSE`)
 *    - Стандартный вывод (`CU_BRM_NORMAL`)
 *    - Минимальный вывод (`CU_BRM_SILENT`)
 * 6. Запускает все тесты с помощью `CU_basic_run_tests()` и выводит их результаты.
 * 7. Очищает реестр и выводит итоговый статус.
 * 
 * @return Возвращает 0, если все тесты прошли успешно, иначе возвращает 1.
 */
int main() {
    // Инициализация CUnit
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Добавление тестов в CUnit
    CU_pSuite pSuiteOutput = CU_add_suite("Output Tests", NULL, NULL);
    CU_pSuite pSuiteMatrix = CU_add_suite("Matrix Tests", NULL, NULL);
    CU_pSuite pSuiteMain = CU_add_suite("Main Tests", NULL, NULL);

    if (pSuiteOutput == NULL || pSuiteMatrix == NULL || pSuiteMain == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Запуск тестов для матриц
    int result_matrix = main_tests_matrix();
    if (result_matrix != 0) {
        printf("Ошибка в тестах матриц (код ошибки: %d)\n", result_matrix);
    }

    // Запуск тестов для вывода
    int result_output = main_tests_output();
    if (result_output != 0) {
        printf("Ошибка в тестах вывода (код ошибки: %d)\n", result_output);
    }

    // Запуск тестов для main.c
    int result_main = main_tests_main();
    if (result_main != 0) {
        printf("Ошибка в тестах main.c (код ошибки: %d)\n", result_main);
    }

    // Завершение работы с CUnit, подробный вывод о результатах тестов
    //вот еще возможные параметры: 
    //CU_BRM_VERBOSE - подробный вывод
    //CU_BRM_SILENT - минимальный вывод
    //CU_BRM_NORMAL - стандартный вывод
    CU_basic_set_mode(CU_BRM_VERBOSE);

    // Функция CU_basic_run_tests(); из библиотеки CUnit запускает все тесты, которые 
    // были добавлены в реестр CUnit через вызовы CU_add_test(), и выводит результаты их выполнения.
    CU_basic_run_tests();

    // Очистка ресурсов
    CU_cleanup_registry();

    printf("Все тесты пройдены успешно!\n");

    // Возвращаем 0, если все тесты прошли успешно, иначе код ошибки
    return (result_matrix == 0 && result_output == 0 && result_main == 0) ? 0 : 1;
}