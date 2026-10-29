#include "matrix.h"

int main() {
    try {
        double arr1[] = {1, 2, 3, 4};
        Matrix A = matrix_from_array(arr1, 2, 2);
        Matrix B = matrix_from_array(arr1, 2, 2);
        
        std::cout << "Matrix A:\n"; print_matrix(A);
        std::cout << "Matrix B:\n"; print_matrix(B);
        
        std::cout << "A + B:\n";
        Matrix C = matrix_add(A, B);
        print_matrix(C);
        
        std::cout << "A * B:\n";
        Matrix D = matrix_multiply(A, B);
        print_matrix(D);
        
        free_matrix(A); free_matrix(B); free_matrix(C); free_matrix(D);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}