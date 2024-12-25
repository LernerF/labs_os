#include "allocator_mckusick.hpp"
#include "allocator_pow2.hpp"
#include "common.hpp"
#include <iostream>
#include <vector>

void test_usage_factor_simple();
void test_alloc_dealloc_simple();

int main() {
    std::cout << "Running simplified tests...\n";

    test_usage_factor_simple();
    test_alloc_dealloc_simple();

    return 0;
}

// Простая проверка фактора использования: всего 10 выделений
void test_usage_factor_simple() {
    std::cout << "=== test_usage_factor_simple ===\n";
    AllocatorMcKusick mckusick(1 << 20); // 1 MB
    AllocatorPow2 pow2(1 << 20);         // 1 MB

    // Сделаем всего 10 выделений
    for (int i = 0; i < 10; ++i) {
        mckusick.allocate(128);
        pow2.allocate(128);
    }

    double mckusick_usage = static_cast<double>(mckusick.get_used_memory()) / (1 << 20);
    double pow2_usage = static_cast<double>(pow2.get_used_memory()) / (1 << 20);

    std::cout << "McKusick usage factor: " << mckusick_usage << "\n";
    std::cout << "Pow2 usage factor: " << pow2_usage << "\n";
}

// Простые тесты на выделение и освобождение
void test_alloc_dealloc_simple() {
    std::cout << "=== test_alloc_dealloc_simple ===\n";
    AllocatorMcKusick mckusick(1 << 20);
    AllocatorPow2 pow2(1 << 20);

    // Выделим и освободим по 10 блоков
    {
        std::vector<void*> blocks;
        for (int i = 0; i < 10; ++i) {
            void* b = mckusick.allocate(128);
            if (!b) {
                std::cerr << "McKusick allocate failed\n";
            }
            blocks.push_back(b);
        }
        for (auto b : blocks) {
            mckusick.deallocate(b);
        }
        std::cout << "McKusick: allocated & deallocated 10 blocks\n";
    }

    {
        std::vector<void*> blocks;
        for (int i = 0; i < 10; ++i) {
            void* b = pow2.allocate(128);
            if (!b) {
                std::cerr << "Pow2 allocate failed\n";
            }
            blocks.push_back(b);
        }
        for (auto b : blocks) {
            pow2.deallocate(b);
        }
        std::cout << "Pow2: allocated & deallocated 10 blocks\n";
    }
}