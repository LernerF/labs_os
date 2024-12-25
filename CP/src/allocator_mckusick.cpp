#include "allocator_mckusick.hpp"
#include <sys/mman.h>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>

AllocatorMcKusick::AllocatorMcKusick(size_t total_size)
    : used_memory(0)
{
    page_size = 4096; // Размер страницы
    memory_pool = mmap(nullptr, total_size, PROT_READ | PROT_WRITE,
                       MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    assert(memory_pool != MAP_FAILED && "Failed to allocate memory pool");

    block_classes = 10; 
    // Предположим, что у нас 10 классов блоков (16, 32, 64, 128, ...)
    free_lists.resize(block_classes, nullptr);
}

AllocatorMcKusick::~AllocatorMcKusick() {
    if (memory_pool) {
        // Выделенный объём — "page_size * block_classes" как в конструкторе
        // или другой логикой, если вы рассчитываете total_size
        munmap(memory_pool, page_size * block_classes);
    }
}

void* AllocatorMcKusick::allocate(size_t size) {
    size_t class_idx = std::ceil(std::log2(size));
    assert(class_idx < block_classes && "Requested size exceeds maximum class");

    // Если нет свободных блоков в этом классе, ставим free_lists[class_idx]
    if (!free_lists[class_idx]) {
        free_lists[class_idx] = static_cast<char*>(memory_pool) + class_idx * page_size;
    }

    void* block = free_lists[class_idx];
    free_lists[class_idx] = static_cast<void*>(static_cast<char*>(block) + (1 << class_idx));

    used_memory += (1 << class_idx);

    // Проверим валидность
    assert(block >= memory_pool &&
           block < static_cast<char*>(memory_pool) + page_size * block_classes);

    return block;
}

void AllocatorMcKusick::deallocate(void* ptr) {
    // Проверяем, что указатель валиден
    if (ptr == nullptr ||
        ptr < memory_pool ||
        ptr >= static_cast<char*>(memory_pool) + page_size * block_classes)
    {
        std::cerr << "Error: Attempt to deallocate invalid pointer\n";
        return;
    }

    // Допустим, мы считаем блок фиксированным 64 байт (упрощённо)
    size_t block_size = 64;
    memset(ptr, 0, block_size);

    used_memory -= block_size;
}

size_t AllocatorMcKusick::get_used_memory() const {
    return used_memory;
}