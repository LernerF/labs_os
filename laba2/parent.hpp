#ifndef PARENT_HPP
#define PARENT_HPP

#include <pthread.h>

// Структура shared memory
struct SharedMemory {
    pthread_mutex_t mutex;
    char data[1024];
};

// Функция родительского процесса
void startParentProcess();

#endif