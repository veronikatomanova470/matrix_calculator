#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>

/**
 * @brief Структура матрицы.
 * Хранит двумерный динамический массив и его размеры.
 * @warning Память освобождается через free_matrix().
 */
typedef struct {
    double** data; ///< Указатель на двумерный массив.
    int rows;      ///< Количество строк.
    int cols;      ///< Количество столбцов.
} Matrix;

Matrix create_matrix(int rows, int cols);
void free_matrix(Matrix m);
Matrix matrix_add(Matrix a, Matrix b);
Matrix matrix_multiply(Matrix a, Matrix b);
void print_matrix(Matrix m);
Matrix matrix_from_array(double* data, int rows, int cols);

// Функция из индивидуального задания (например, Транспонирование - задание 11)
Matrix matrix_transpose(Matrix m);

#endif // MATRIX_H