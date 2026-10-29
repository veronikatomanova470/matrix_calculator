#include "matrix.h"
#include <iomanip>

/**
 * @brief Создание матрицы заданного размера.
 * 
 * @param rows Количество строк (> 0).
 * @param cols Количество столбцов (> 0).
 * @return Matrix Инициализированная нулями матрица.
 * @exception std::invalid_argument Если rows <= 0 или cols <= 0.
 */
Matrix create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive integers");
    }
    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.data = new double*[rows];
    for (int i = 0; i < rows; i++) {
        mat.data[i] = new double[cols];
        for (int j = 0; j < cols; j++) mat.data[i][j] = 0.0;
    }
    return mat;
}

/**
 * @brief Освобождение памяти матрицы.
 * 
 * @param m Матрица, память которой нужно освободить.
 */
void free_matrix(Matrix m) {
    if (m.data == nullptr) return;
    for (int i = 0; i < m.rows; i++) {
        if (m.data[i] != nullptr) {
            delete[] m.data[i];
        }
    }
    delete[] m.data;
}

/**
 * @brief Сложение двух матриц.
 * 
 * @param a Первая матрица.
 * @param b Вторая матрица.
 * @return Matrix Результирующая матрица.
 * @exception std::invalid_argument Если размеры матриц не совпадают.
 */
Matrix matrix_add(Matrix a, Matrix b) {
    if (a.rows != b.rows || a.cols != b.cols) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }
    Matrix c = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++)
        for (int j = 0; j < a.cols; j++)
            c.data[i][j] = a.data[i][j] + b.data[i][j];
    return c;
}

/**
 * @brief Умножение двух матриц.
 * 
 * Выполняет перемножение матриц A и B с проверкой совместимости размеров.
 * Алгоритм оптимизирован по памяти: результат вычисляется в новую матрицу
 * без создания промежуточных копий данных.
 * 
 * @param a Первая матрица (левая), размер M x N.
 * @param b Вторая матрица (правая), размер N x K.
 * @return Matrix Результирующая матрица размером M x K.
 * 
 * @exception std::invalid_argument Если количество столбцов матрицы A не равно количеству строк матрицы B.
 * @exception std::bad_alloc Если не удалось выделить память под результирующую матрицу.
 */
Matrix matrix_multiply(Matrix a, Matrix b) {
    if (a.cols != b.rows) {
        throw std::invalid_argument("Matrix dimensions mismatch for multiplication");
    }

    Matrix c = create_matrix(a.rows, b.cols);

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            double sum = 0.0;
            for (int k = 0; k < a.cols; k++) {
                sum += a.data[i][k] * b.data[k][j];
            }
            c.data[i][j] = sum;
        }
    }

    return c;
}

// --- ИНДИВИДУАЛЬНОЕ ЗАДАНИЕ (Пример 11: Транспонирование) ---
/**
 * @brief Транспонирование матрицы.
 * 
 * @param m Исходная матрица.
 * @return Matrix Транспонированная матрица.
 */
Matrix matrix_transpose(Matrix m) {
    Matrix t = create_matrix(m.cols, m.rows);
    for (int i = 0; i < m.rows; i++)
        for (int j = 0; j < m.cols; j++)
            t.data[j][i] = m.data[i][j];
    return t;
}
// -------------------------------------------------------------

/**
 * @brief Создание матрицы из одномерного массива.
 * 
 * @param data Указатель на массив данных.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @return Matrix Созданная матрица.
 */
Matrix matrix_from_array(double* data, int rows, int cols) {
    Matrix m = create_matrix(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            m.data[i][j] = data[i * cols + j];
    return m;
}

/**
 * @brief Вывод матрицы в консоль.
 * 
 * @param m Матрица для вывода.
 */
void print_matrix(Matrix m) {
    if (m.data == nullptr) return;
    std::cout << std::fixed << std::setprecision(2);
    for (int i = 0; i < m.rows; i++) {
        std::cout << "[ ";
        for (int j = 0; j < m.cols; j++) {
            std::cout << std::setw(6) << m.data[i][j] << " ";
        }
        std::cout << "]\n";
    }
}