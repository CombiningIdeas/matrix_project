#pragma once



/**
 * @file tests_main.h
 * @brief Заголовочный файл для тестирования главной программы.
 * 
 * В этом файле содержатся объявления функций, предназначенных для тестирования
 * основных компонентов программы, включая тесты на успешную загрузку матриц и
 * обработку ошибок при отсутствии необходимых файлов.
 * 
 * Этот файл используется в сочетании с CUnit для выполнения юнит-тестирования.
 */



/**
 * @brief Тест успешной загрузки матриц и выполнения вычислений.
 * 
 * Эта функция выполняет тест, который проверяет успешную загрузку всех необходимых файлов
 * и выполнение вычислений в программе без ошибок.
 */
void test_main_success();

/**
 * @brief Тест на ошибку при отсутствии одного из файлов.
 * 
 * Эта функция выполняет тест, который симулирует ошибку при отсутствии одного из файлов
 * (например, файл A.txt). В случае отсутствия файла программа должна вернуть ошибку.
 */
void test_main_failure();

/**
 * @brief Главная функция для запуска тестов.
 * 
 * Эта функция инициализирует и запускает тесты, определенные для основного компонента программы.
 * Она добавляет тесты в тестовый набор и сообщает о результате выполнения тестов.
 * 
 * @return 0 в случае успешного выполнения тестов, в противном случае возвращает код ошибки.
 */
int main_tests_main();

