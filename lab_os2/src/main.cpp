#include <iostream>
#include <pthread.h>
#include "matrix_utils.h"
#include "median_filter.h"  // MAX_THREADS, thread_function

int main() {
    rows = 6;
    cols = 6;
    window_size = 3;
    K = 1;

    initialize_matrix(rows, cols);

    std::cout << "Original Matrix:\n";
    print_matrix(matrix, rows, cols);

    pthread_t threads[MAX_THREADS];
    for (int i = 0; i < MAX_THREADS; i++) {
        int *thread_id = new int(i);
        pthread_create(&threads[i], nullptr, thread_function, thread_id);
    }

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], nullptr);
    }

    std::cout << "Filtered Matrix:\n";
    print_matrix(matrix, rows, cols);

    free_matrix(rows);

    pthread_mutex_destroy(&mutex); // Корректное завершение работы с мьютексом
    return 0;
}