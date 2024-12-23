#include <gtest/gtest.h>
#include "matrix_utils.h"
#include "median_filter.h"
#include <iostream>

struct DisableCout {
    std::streambuf* old_buf;
    DisableCout() {
        old_buf = std::cout.rdbuf();  
        std::cout.rdbuf(nullptr);   
    }
    ~DisableCout() {
        std::cout.rdbuf(old_buf);    
    }
};

// Проверка корректности на простой матрице 3x3
TEST(MedianFilter, BasicFunctionality) {
    DisableCout disableCout;  

    rows = 3;
    cols = 3;
    window_size = 3;
    K = 1;

    initialize_matrix(rows, cols);

    matrix[0][0] = 1; matrix[0][1] = 2; matrix[0][2] = 3;
    matrix[1][0] = 4; matrix[1][1] = 5; matrix[1][2] = 6;
    matrix[2][0] = 7; matrix[2][1] = 8; matrix[2][2] = 9;

    apply_median_filter_segment(0, rows);

    EXPECT_GT(matrix[1][1], 0);  

    free_matrix(rows);
}

// Проверка многопоточности на матрице 4x4
TEST(MedianFilter, Multithreading) {
    DisableCout disableCout;  // Отключаем вывод

    rows = 4;
    cols = 4;
    window_size = 3;
    K = 1;

    initialize_matrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j + 1;
        }
    }

    pthread_t threads[MAX_THREADS];
    for (int i = 0; i < MAX_THREADS; i++) {
        int *thread_id = new int(i);
        pthread_create(&threads[i], nullptr, thread_function, thread_id);
    }
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], nullptr);
    }

    EXPECT_GT(matrix[1][1], 0);  

    free_matrix(rows);
}

// Тест 3: Проверка на время
TEST(MedianFilter, LargeMatrix) {
    DisableCout disableCout;  // Отключаем вывод

    rows = 100;
    cols = 100;
    window_size = 3;
    K = 1;

    initialize_matrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 256;
        }
    }

    // Применяем медианный фильтр в однопоточном режиме
    apply_median_filter_segment(0, rows);

    EXPECT_GT(matrix[rows / 2][cols / 2], 0);

    free_matrix(rows);
}