#include "allocator_mckusick.hpp"
#include "allocator_pow2.hpp"
#include "common.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <map> // Добавлен заголовочный файл для std::map

int main() {
    AllocatorMcKusick mckusick(1 << 20); // 1 MB
    AllocatorPow2 pow2(1 << 20);         // 1 MB

    std::cout << "Memory Allocator Program\n";
    std::cout << "Available commands:\n";
    std::cout << "  allocate <allocator_type> <size>   - Allocate memory block\n";
    std::cout << "  deallocate <allocator_type> <ptr> - Deallocate memory block\n";
    std::cout << "  exit                              - Exit the program\n";
    std::cout << "allocator_type: 1 = McKusick, 2 = Pow2\n";

    std::string command;
    std::map<void*, int> allocated_blocks; // Исправлено: Подключен std::map для хранения информации

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command == "exit") {
            break;
        }

        std::istringstream iss(command);
        std::string cmd;
        iss >> cmd;

        if (cmd == "allocate") {
            int allocator_type;
            size_t size;
            iss >> allocator_type >> size;

            if (allocator_type != 1 && allocator_type != 2) {
                std::cerr << "Invalid allocator_type. Use 1 for McKusick, 2 for Pow2.\n";
                continue;
            }

            void* block = nullptr;
            if (allocator_type == 1) {
                block = mckusick.allocate(size);
            } else if (allocator_type == 2) {
                block = pow2.allocate(size);
            }

            if (block) {
                allocated_blocks[block] = allocator_type; // Сохраняем информацию о блоке
                std::cout << "Allocated " << size << " bytes at address " << block << "\n";
            } else {
                std::cerr << "Allocation failed.\n";
            }

        } else if (cmd == "deallocate") {
            int allocator_type;
            void* ptr;
            iss >> allocator_type >> ptr;

            if (allocator_type != 1 && allocator_type != 2) {
                std::cerr << "Invalid allocator_type. Use 1 for McKusick, 2 for Pow2.\n";
                continue;
            }

            if (allocated_blocks.find(ptr) == allocated_blocks.end()) {
                std::cerr << "Invalid pointer or block not allocated.\n";
                continue;
            }

            if (allocated_blocks[ptr] != allocator_type) {
                std::cerr << "Block allocated with different allocator.\n";
                continue;
            }

            if (allocator_type == 1) {
                mckusick.deallocate(ptr);
            } else if (allocator_type == 2) {
                pow2.deallocate(ptr);
            }

            allocated_blocks.erase(ptr); // Удаляем информацию о блоке
            std::cout << "Deallocated block at address " << ptr << "\n";

        } else {
            std::cerr << "Unknown command. Available commands: allocate, deallocate, exit.\n";
        }
    }

    std::cout << "Exiting program.\n";
    return 0;
}