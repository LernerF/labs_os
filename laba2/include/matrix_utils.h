#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

extern int **matrix, **result;
extern int rows, cols, window_size, K;

void initialize_matrix(int r, int c);
void free_matrix(int r);
void print_matrix(int **mat, int r, int c);

#endif