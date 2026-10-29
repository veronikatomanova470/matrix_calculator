#include <gtest/gtest.h>
#include "matrix.h"
#include <stdexcept>

// 1. НОРМАЛЬНЫЕ СЛУЧАИ
TEST(MatrixTest, CreateMatrix_NormalCase) {
    Matrix A = create_matrix(3, 4);
    EXPECT_EQ(A.rows, 3);
    EXPECT_EQ(A.cols, 4);
    EXPECT_NE(A.data, nullptr);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_DOUBLE_EQ(A.data[i][j], 0.0);
        }
    }
    free_matrix(A);
}

TEST(MatrixTest, Addition_NormalCase) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);
    A.data[0][0] = 1; A.data[0][1] = 2; A.data[1][0] = 3; A.data[1][1] = 4;
    B.data[0][0] = 5; B.data[0][1] = 6; B.data[1][0] = 7; B.data[1][1] = 8;
    
    Matrix C = matrix_add(A, B);
    EXPECT_DOUBLE_EQ(C.data[0][0], 6.0);
    EXPECT_DOUBLE_EQ(C.data[0][1], 8.0);
    EXPECT_DOUBLE_EQ(C.data[1][0], 10.0);
    EXPECT_DOUBLE_EQ(C.data[1][1], 12.0);
    
    free_matrix(A); free_matrix(B); free_matrix(C);
}

TEST(MatrixTest, Multiplication_NormalCase) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);
    A.data[0][0] = 1; A.data[0][1] = 2; A.data[1][0] = 3; A.data[1][1] = 4;
    B.data[0][0] = 5; B.data[0][1] = 6; B.data[1][0] = 7; B.data[1][1] = 8;
    
    Matrix C = matrix_multiply(A, B);
    EXPECT_DOUBLE_EQ(C.data[0][0], 19.0);
    EXPECT_DOUBLE_EQ(C.data[0][1], 22.0);
    EXPECT_DOUBLE_EQ(C.data[1][0], 43.0);
    EXPECT_DOUBLE_EQ(C.data[1][1], 50.0);
    
    free_matrix(A); free_matrix(B); free_matrix(C);
}

// Тест для индивидуального задания (Транспонирование)
TEST(MatrixTest, Transpose_NormalCase) {
    Matrix A = create_matrix(2, 3);
    A.data[0][0] = 1; A.data[0][1] = 2; A.data[0][2] = 3;
    A.data[1][0] = 4; A.data[1][1] = 5; A.data[1][2] = 6;
    
    Matrix T = matrix_transpose(A);
    EXPECT_EQ(T.rows, 3);
    EXPECT_EQ(T.cols, 2);
    EXPECT_DOUBLE_EQ(T.data[0][0], 1.0);
    EXPECT_DOUBLE_EQ(T.data[1][0], 2.0);
    EXPECT_DOUBLE_EQ(T.data[2][1], 6.0);
    
    free_matrix(A); free_matrix(T);
}

// 2. НЕКОРРЕКТНЫЕ СЛУЧАИ (Проверка исключений)
TEST(MatrixTest, CreateMatrix_NegativeCols) {
    EXPECT_THROW(create_matrix(3, -1), std::invalid_argument);
}

TEST(MatrixTest, Addition_SizeMismatch) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(3, 3);
    EXPECT_THROW(matrix_add(A, B), std::invalid_argument);
    free_matrix(A); free_matrix(B);
}

TEST(MatrixTest, Multiplication_SizeMismatch) {
    Matrix A = create_matrix(2, 3);
    Matrix B = create_matrix(2, 2);
    EXPECT_THROW(matrix_multiply(A, B), std::invalid_argument);
    free_matrix(A); free_matrix(B);
}