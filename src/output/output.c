#include <stdio.h>
#include "../matrix/matrix.h"
#include "../../include/config.h"


//Выводит матрицу в консоль
void print_matrix(const Matrix* matrix) {
    //если матрица существует, то выводим матрицу
    if (matrix) {
        for (int row = 0; row < matrix->rows; row++) {
            for (int col = 0; col < matrix->cols; col++) {
                printf("%lf ", matrix->data[row][col]);
            }
            printf("\n");
        }
    }
}


//Сохраняет матрицу в текстовый файл
int save_matrix_to_file(const Matrix* matrix, const char* filename) {
    int result = -1;//На случай, если какой-то кусок кода завершит свою работу с ошибкой

    //Если матрицы сущестует, то продолжаем работу
    if (matrix) {

        FILE* file = fopen(filename, "w");//Открываем файл

        //Если файл открылся, то продолжаем работу
        if (file) {
            fprintf(file, "Number of rows: %d\n; Number of columns: %d\n;", matrix->rows, matrix->cols);

            for (int row = 0; row < matrix->rows; row++) {
                for (int col = 0; col < matrix->cols; col++) {
                    fprintf(file, "%lf ", matrix->data[row][col]);
                }
                fprintf(file, "\n");//Делаем переход на следующую строку
            }

            fclose(file);//Когда вывели в файл все что нужно закрываем файл
            result = 0;//Если работа выполонилась успешно и весь код отработал, то вернем 0
        }
    }

    return result;
}
