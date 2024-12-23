#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H

#include <pthread.h>

// Переменные и параметры должны быть объявлены как extern, если они определены в другом .cpp
extern int rows;
extern int cols;
extern int window_size;
extern int K;
extern int **matrix;
extern int **result;
extern pthread_mutex_t mutex;

// Определите MAX_THREADS в заголовочном файле
#define MAX_THREADS 4

// Объявление функции для применения медианного фильтра к сегменту
void apply_median_filter_segment(int start_row, int end_row);

// Объявление поточной функции
void* thread_function(void* arg);

#endif // MEDIAN_FILTER_H