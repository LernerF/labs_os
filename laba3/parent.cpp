#include "parent.hpp"
#include <iostream>
#include <pthread.h>
#include <cstring>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#define SHM_NAME "/shared_memory_example"
#define SHM_SIZE sizeof(SharedMemory)

void startParentProcess() {
    // Подключаемся к shared memory
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open failed");
        exit(1);
    }

    auto *shared_memory = static_cast<SharedMemory *>(mmap(nullptr, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0));
    if (shared_memory == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    // Работаем с пользователем
    std::string input;
    std::cout << "Введите строку: ";
    while (std::getline(std::cin, input)) {
        // Блокируем доступ к данным
        pthread_mutex_lock(&shared_memory->mutex_data);

        // Записываем строку
        strncpy(shared_memory->data, input.c_str(), sizeof(shared_memory->data) - 1);
        shared_memory->data[input.size()] = '\0';

        // Разблокируем доступ к данным
        pthread_mutex_unlock(&shared_memory->mutex_data);

        // Ждём завершения обработки
        pthread_mutex_lock(&shared_memory->mutex_flow);

        // Выводим обработанную строку
        std::cout << "Обработанная строка: " << shared_memory->data << std::endl;

        std::cout << "Введите строку: ";
    }

    munmap(shared_memory, SHM_SIZE);
}