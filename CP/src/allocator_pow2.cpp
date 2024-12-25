#include "allocator_pow2.hpp"
#include <sys/mman.h>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>

AllocatorPow2::AllocatorPow2(size_t total_size_param)
    : used_memory(0), total_size(total_size_param)
{
    // max_block_size: максимальный размер ОДНОГО блока,
    // а не размер всей памяти
    max_block_size = 1024; // 1 KB, условно

    // Выделяем "total_size_param" байт через mmap
    memory_pool = mmap(nullptr, total_size, PROT_READ | PROT_WRITE,
                       MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    assert(memory_pool != MAP_FAILED && "Failed to allocate memory pool");

    // Инициализация списков свободных блоков
    free_lists.resize(static_cast<size_t>(std::log2(max_block_size)) + 1, nullptr);
}

AllocatorPow2::~AllocatorPow2() {
    if (memory_pool) {
        munmap(memory_pool, total_size);
    }
}

void* AllocatorPow2::allocate(size_t size) {
    // 1. Если запрос больше, чем max_block_size, не можем выделить
    if (size > max_block_size) {
        std::cerr << "Error: Requested size (" << size
                  << ") exceeds max_block_size (" << max_block_size << ")\n";
        return nullptr;
    }

    // 2. Определяем класс
    size_t class_idx = std::ceil(std::log2(size));
    assert(class_idx < free_lists.size() && "Requested size exceeds maximum class");

    // 3. Если ещё не инициализировали free_lists[class_idx], сделаем это
    if (!free_lists[class_idx]) {
        // Предположим (упрощённо), что каждый class_idx начинает с offset = class_idx * max_block_size
        // При большом числе выделений можно «уйти» далеко вперёд, но для учебных целей достаточно
        free_lists[class_idx] =
            static_cast<char*>(memory_pool) + class_idx * max_block_size;
    }

    void* block = free_lists[class_idx];

    // 4. Проверка, что block не выходит за пределы памяти
    //    т.к. mmap выделил total_size
    assert(block >= memory_pool &&
           block < static_cast<char*>(memory_pool) + total_size &&
           "Block pointer is out of mapped range");

    // 5. Сдвигаем free_lists[class_idx]
    free_lists[class_idx] =
        static_cast<char*>(free_lists[class_idx]) + (1 << class_idx);

    // 6. Проверяем, что новый адрес всё ещё в пределах total_size
    {
        char* new_pointer = static_cast<char*>(free_lists[class_idx]);
        if (new_pointer > static_cast<char*>(memory_pool) + total_size) {
            std::cerr << "Error: Not enough memory in class " << class_idx << "\n";
            return nullptr;
        }
    }

    // 7. Увеличиваем счётчик используемой памяти
    used_memory += (1 << class_idx);

    return block;
}

void AllocatorPow2::deallocate(void* ptr) {
    if (ptr == nullptr ||
        ptr < memory_pool ||
        ptr >= static_cast<char*>(memory_pool) + total_size)
    {
        std::cerr << "Error: Attempt to deallocate invalid pointer\n";
        return;
    }

    // Упрощённо считаем, что блок = 64 байт
    size_t block_size = 64;
    memset(ptr, 0, block_size);
    used_memory -= block_size;
}

size_t AllocatorPow2::get_used_memory() const {
    return used_memory;
}