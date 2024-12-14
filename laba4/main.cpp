#include <iostream>
#include "rectangle.h"

int main() {
    try {
        int choice;
        std::cout << "Choose an operation:\n"
                  << "1. Calculate area\n"
                  << "2. Convert number to binary\n";
        std::cin >> choice;

        if (choice == 1) {
            float A, B;
            std::cout << "Enter sides A and B: ";
            std::cin >> A >> B;

            std::cout << "Area: " << Square(A, B) << "\n";
        } else if (choice == 2) {
            long x;
            std::cout << "Enter a number: ";
            std::cin >> x;

            std::cout << "Binary: " << translation(x) << "\n";
        } else {
            std::cerr << "Invalid choice.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}