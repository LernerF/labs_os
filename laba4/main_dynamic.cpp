#include <iostream>
#include <dlfcn.h>
#include <stdexcept>

int main() {
    try {
        const char* libraries[] = {"./librectangle.so", "./libtriangle.so"};
        int currentLib = 0;

        void* handle = dlopen(libraries[currentLib], RTLD_LAZY);
        if (!handle) {
            throw std::runtime_error(dlerror());
        }

        auto Square = (float (*)(float, float))dlsym(handle, "Square");
        auto translation = (char* (*)(long))dlsym(handle, "translation");
        if (!Square || !translation) {
            dlclose(handle);
            throw std::runtime_error(dlerror());
        }

        int choice;
        std::cout << "Choose an operation:\n"
                  << "0. Switch library\n"
                  << "1. Calculate area\n"
                  << "2. Convert number to another system\n";

        while (std::cin >> choice) {
            if (choice == 0) {
                dlclose(handle);
                currentLib = 1 - currentLib;
                handle = dlopen(libraries[currentLib], RTLD_LAZY);
                if (!handle) {
                    throw std::runtime_error(dlerror());
                }

                Square = (float (*)(float, float))dlsym(handle, "Square");
                translation = (char* (*)(long))dlsym(handle, "translation");
                if (!Square || !translation) {
                    dlclose(handle);
                    throw std::runtime_error(dlerror());
                }

                std::cout << "Switched to " << libraries[currentLib] << "\n";
            } else if (choice == 1) {
                float A, B;
                std::cout << "Enter sides A and B: ";
                std::cin >> A >> B;

                std::cout << "Area: " << Square(A, B) << "\n";
            } else if (choice == 2) {
                long x;
                std::cout << "Enter a number: ";
                std::cin >> x;

                std::cout << "Converted: " << translation(x) << "\n";
            } else {
                std::cerr << "Invalid choice.\n";
            }

            std::cout << "\nChoose an operation:\n"
                      << "0. Switch library\n"
                      << "1. Calculate area\n"
                      << "2. Convert number to another system\n";
        }

        dlclose(handle);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}