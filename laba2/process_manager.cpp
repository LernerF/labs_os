#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "parent.hpp"

#define SHM_NAME "/shared_memory_example"
#define SHM_SIZE sizeof(SharedMemory)

void startProcessManager() {
    // Создаём shared memory
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open failed");
        exit(1);
    }

    // Устанавливаем размер shared memory
    if (ftruncate(shm_fd, SHM_SIZE) == -1) {
        perror("ftruncate failed");
        exit(1);
    }

    // Отображаем shared memory
    auto *shared_memory = static_cast<SharedMemory *>(mmap(nullptr, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0));
    if (shared_memory == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    // Инициализируем мьютексы
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);

    pthread_mutex_init(&shared_memory->mutex_data, &attr);
    pthread_mutex_init(&shared_memory->mutex_flow, &attr);

    pthread_mutexattr_destroy(&attr);

    // Блокируем mutex_flow для синхронизации
    pthread_mutex_lock(&shared_memory->mutex_flow);

    // Создаём первый дочерний процесс
    pid_t child1_pid = fork();
    if (child1_pid == -1) {
        perror("fork failed");
        exit(1);
    }

    if (child1_pid == 0) {
        // Запускаем child1 через exec
        execl("./child1", "./child1", nullptr);
        perror("execl failed");
        exit(1);
    }

    // Создаём второй дочерний процесс
    pid_t child2_pid = fork();
    if (child2_pid == -1) {
        perror("fork failed");
        exit(1);
    }

    if (child2_pid == 0) {
        // Запускаем child2 через exec
        execl("./child2", "./child2", nullptr);
        perror("execl failed");
        exit(1);
    }

    // Ожидание завершения дочерних процессов
    waitpid(child1_pid, nullptr, 0);
    waitpid(child2_pid, nullptr, 0);

    // Уничтожаем shared memory
    munmap(shared_memory, SHM_SIZE);
    shm_unlink(SHM_NAME);
}

int main() {
    startProcessManager();
    return 0;
}