#include "child1.hpp"
#include "utils.hpp"
#include <pthread.h>
#include <cstring>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#define SHM_NAME "/shared_memory_example"
#define SHM_SIZE sizeof(SharedMemory)

int main() {
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

    // Обрабатываем строку
    pthread_mutex_lock(&shared_memory->mutex_data);
    if (strlen(shared_memory->data) > 0) {
        toUpperCase(shared_memory->data);
    }
    pthread_mutex_unlock(&shared_memory->mutex_data);

    return 0;
}