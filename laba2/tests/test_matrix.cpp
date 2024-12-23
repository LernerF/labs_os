#include <gtest/gtest.h>
#include "matrix_utils.h"

TEST(MatrixUtils, InitializeMatrix) {
    rows = 3;
    cols = 3;
    initialize_matrix(rows, cols);

    ASSERT_NE(matrix, nullptr);
    ASSERT_NE(result, nullptr);

    // Проверка корректности инициализации
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            EXPECT_GE(matrix[i][j], 0);
            EXPECT_LT(matrix[i][j], 256);
        }
    }

    free_matrix(rows);
}

TEST(MatrixUtils, FreeMatrix) {
    rows = 3;
    cols = 3;
    initialize_matrix(rows, cols);
    free_matrix(rows);

    EXPECT_EQ(matrix, nullptr);
    EXPECT_EQ(result, nullptr);
}