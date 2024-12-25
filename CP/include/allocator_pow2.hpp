#ifndef ALLOCATOR_POW2_HPP
#define ALLOCATOR_POW2_HPP

#include "common.hpp"
#include <vector>

class AllocatorPow2 {
public:
    explicit AllocatorPow2(size_t total_size);
    ~AllocatorPow2();

    void* allocate(size_t size);
    void deallocate(void* ptr);
    size_t get_used_memory() const;

private:
    void* memory_pool;               // Указатель на общий пул памяти
    std::vector<void*> free_lists;   // Списки свободных блоков
    size_t max_block_size;           // Максимальный размер одного блока
    size_t used_memory;              // Счётчик используемой памяти
    size_t total_size;               // Общий объём замапленной памяти
};

#endif // ALLOCATOR_POW2_HPP