#include "matrix.h"


//Создает новую матрицу с заданными размерами
Matrix* create_matrix(int rows, int cols) {
    Matrix* matrix = NULL;

    // Проверяем, что количество строк и столбцов больше 0
    if (rows > 0 && cols > 0) {
        matrix = (Matrix*)malloc(sizeof(Matrix));  // Выделяем память для самой матрицы
        // Продолжаем создание матрицы если память выделилась
        if (matrix) {
            matrix->rows = rows;
            matrix->cols = cols;
            matrix->data = (MATRIX_TYPE**)malloc(rows * sizeof(MATRIX_TYPE*));  // Выделяем память для указателей на строки
            if (matrix->data) {
                // Выделяем память для каждой строки матрицы
                for (int iter = 0; iter < rows; iter++) {
                    matrix->data[iter] = (MATRIX_TYPE*)malloc(cols * sizeof(MATRIX_TYPE));  // Память для данных строки
                    // Если не удалось выделить память для строки, освобождаем все ранее выделенные строки
                    if (!matrix->data[iter])
                        free_matrix(matrix);
                }
            } else {
                //Если память для указателей на строки не выделилась то просто очищаем память
                free(matrix);
                matrix = NULL;
            }
        }
    }

    return matrix;
}


//Освобождает память, выделенную под матрицу
void free_matrix(Matrix* matrix) {
    for (int iter = 0; iter < matrix->rows; iter++) {
        free(matrix->data[iter]);
    }

    free(matrix->data);
    free(matrix);
}


//Загружает матрицу из текстового файла
Matrix* load_matrix_from_file(const char* filename) {
    Matrix* matrix = NULL;
    FILE* file = fopen(filename, "r");

    // Если файл есть
    if (file) {
        int rows, cols;
        // Считывание размеров матрицы (количество строк и столбцов)
        if (fscanf(file, "%d %d", &rows, &cols) == 2) {
            matrix = create_matrix(rows, cols);
            if (matrix) {
                // Считывание элементов матрицы
                for (int row = 0; row < rows; row++) {
                    for (int col = 0; col < cols; col++) {
                        if (fscanf(file, "%lf", &matrix->data[row][col]) != 1) {
                            // Если чтение элемента матрицы не удалось, освобождаем память и возвращаем NULL
                            free_matrix(matrix);
                            matrix = NULL;//затираем матрицу
                            break;
                        }
                    }
                    if (matrix == NULL) 
                        break;
                }
            }
        }
        fclose(file);
    }

    return matrix;
}


//Копирует матрицу
Matrix* copy_matrix(const Matrix* source) {
    // Инициализация указателя на результат копирования
    Matrix* copy = NULL;

    //Если матрица есть, то продолжаем копирование
    if (source) {

         // Создание новой матрицы с теми же размерами, что и у исходной
        copy = create_matrix(source->rows, source->cols);

        // Копирование элементов матрицы
        if (copy)
            for (int row = 0; row < source->rows; row++)
                for (int col = 0; col < source->cols; col++)
                    copy->data[row][col] = source->data[row][col];
    }

    return copy;//возвращаем копию
}


//Складывает две матрицы
Matrix* add_matrices(const Matrix* A, const Matrix* B) {
    // Инициализация указателя на результат сложения
    Matrix* result = NULL;

    // Проверяем, что обе матрицы существуют, и их размеры совпадают
    if (A && B && A->rows == B->rows && A->cols == B->cols) {

        // Создаем новую матрицу для хранения результата
        result = create_matrix(A->rows, A->cols);

        // Складываем соответствующие элементы двух матриц
        if (result)
            for (int row = 0; row < A->rows; row++) 
                for (int col = 0; col < A->cols; col++) 
                    result->data[row][col] = A->data[row][col] + B->data[row][col];
    }

    return result;//возвращаем сложенные матрицы
}


//Умножает две матрицы
Matrix* multiply_matrices(const Matrix* A, const Matrix* B) {
    // Инициализация указателя на результат умножения
    Matrix* result = NULL;

    // Проверка, что обе матрицы существуют и что количество столбцов первой матрицы
    // равно количеству строк второй матрицы (условие для умножения)
    if (A && B && A->cols == B->rows) {
        result = create_matrix(A->rows, B->cols);

        // Перемножаем строки первой матрицы и столбцы второй матрицы
        // Выполняем суммирование произведений соответствующих элементов
        if (result)
            for (int row = 0; row < A->rows; row++) 
                for (int col = 0; col < B->cols; col++) 
                    for (int iter = 0; iter < A->cols; iter++)
                        result->data[row][col] += A->data[row][iter] * B->data[iter][col];
    }

    return result;//возвращаем умноженные матрицы
}


// Транспонирует матрицу
Matrix* transpose_matrix(const Matrix* matrix) {
    // Инициализация указателя на результат транспонирования матрицы
    Matrix* result = NULL;

    //Если матрица еcть, то трансопнируем матрицу
    if (matrix) {
        // Создание новой матрицы с перевернутыми размерами (строки становятся столбцами)
        result = create_matrix(matrix->cols, matrix->rows);
        
        if (result) 
            for (int row = 0; row < matrix->rows; row++) 
                for (int col = 0; col < matrix->cols; col++) 
                    result->data[col][row] = matrix->data[row][col];
    }

    return result;//возвращаем транспонированную матрицу
}


//Вычисляет детерминант квадратной матрицы
MATRIX_TYPE determinant(const Matrix* matrix) {
    // Инициализация переменной для хранения значения детерминанта
    MATRIX_TYPE det = 0;

    // Проверка, что матрица существует и является квадратной (количество строк = количество столбцов)
    if (matrix && matrix->rows == matrix->cols) {
        if (matrix->rows == 2) {
            det = matrix->data[0][0] * matrix->data[1][1] - matrix->data[0][1] * matrix->data[1][0];
        } else {
            // Для матриц размером больше 2x2 используем разложение по первой строке
            // То есть метод минора
            for (int row = 0; row < matrix->cols; row++) {
                Matrix* submatrix = create_matrix(matrix->rows - 1, matrix->cols - 1);

                // Заполнение подматрицы, копируя элементы из исходной матрицы, пропуская строку и столбец
                if (submatrix) {
                    for (int iter = 1; iter < matrix->rows; iter++)
                        for (int col = 0; col < matrix->cols; col++)       
                            if (col != row) // Копируем элементы, пропуская столбец и строку
                                submatrix->data[iter - 1][col < row ? col : col - 1] = matrix->data[iter][col];

                    // Разложение по первой строке: 
                    // - чередование знаков (по принципу миноров)
                    // - рекурсивный вызов функции для вычисления детерминанта подматрицы
                    det += (row % 2 == 0 ? 1 : -1) * matrix->data[0][row] * determinant(submatrix);

                    // Освобождаем память для подматрицы
                    free_matrix(submatrix);
                }
            }
        }
    }

    return det;//возвращаем детерминант
}
