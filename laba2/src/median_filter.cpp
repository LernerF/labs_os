#include "median_filter.h"
#include "matrix_utils.h"
#include <algorithm>
#include <pthread.h>
#include <vector>

// Глобальный мьютекс
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Функция для применения медианного фильтра к сегменту матрицы
void apply_median_filter_segment(int start_row, int end_row) {
    for (int k = 0; k < K; k++) {  // Применяем фильтр K раз
        for (int i = start_row; i < end_row; i++) {
            for (int j = 0; j < cols; j++) {
                std::vector<int> window;

                // Формируем окно
                for (int wi = -window_size / 2; wi <= window_size / 2; wi++) {
                    for (int wj = -window_size / 2; wj <= window_size / 2; wj++) {
                        int ni = i + wi, nj = j + wj;
                        if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                            window.push_back(matrix[ni][nj]);
                        }
                    }
                }

                // Сортируем окно и находим медиану
                std::sort(window.begin(), window.end());
                result[i][j] = window[window.size() / 2];
            }
        }

        // Синхронизация: копируем результат обратно в исходную матрицу
        pthread_mutex_lock(&mutex);
        for (int i = start_row; i < end_row; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = result[i][j];
            }
        }
        pthread_mutex_unlock(&mutex);
    }
}

// Функция, используемая в потоках
void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    delete (int*)arg;  // Освобождаем память для идентификатора потока

    // Расчёт диапазона строк для обработки потоком
    int start_row = (rows / MAX_THREADS) * thread_id;
    int end_row = (thread_id == MAX_THREADS - 1) ? rows : start_row + (rows / MAX_THREADS);

    apply_median_filter_segment(start_row, end_row);
    pthread_exit(nullptr);
}