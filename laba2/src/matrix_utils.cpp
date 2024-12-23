#include <iostream>
#include <cstdlib>
#include "matrix_utils.h"

int rows = 0, cols = 0, window_size = 0, K = 0; 
int **matrix = nullptr, **result = nullptr;
void initialize_matrix(int r, int c) {
    matrix = new int *[r];
    result = new int *[r];
    for (int i = 0; i < r; i++) {
        matrix[i] = new int[c];
        result[i] = new int[c];
        for (int j = 0; j < c; j++) {
            matrix[i][j] = rand() % 256;
        }
    }
}

void free_matrix(int r) {
    for (int i = 0; i < r; i++) {
        delete[] matrix[i];
        delete[] result[i];
    }
    delete[] matrix;
    delete[] result;

    matrix = nullptr;
    result = nullptr;
}

void print_matrix(int **mat, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << "\n";
    }
}