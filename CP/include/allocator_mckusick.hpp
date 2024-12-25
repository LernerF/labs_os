#ifndef ALLOCATOR_MCKUSICK_HPP
#define ALLOCATOR_MCKUSICK_HPP

#include "common.hpp"
#include <vector>

class AllocatorMcKusick {
public:
    explicit AllocatorMcKusick(size_t total_size);
    ~AllocatorMcKusick();

    void* allocate(size_t size);
    void deallocate(void* ptr);
    size_t get_used_memory() const;

private:
    void* memory_pool;               // Указатель на общий пул памяти
    std::vector<void*> free_lists;   // Массив списков свободных блоков
    size_t block_classes;            // Количество классов блоков
    size_t page_size;                // Размер страницы памяти
    size_t used_memory;              // Общее количество используемой памяти
};

#endif // ALLOCATOR_MCKUSICK_HPP