#include "triangle.h"
#include <cstdio>
#include <cstring>

float Square(float A, float B) {
    return 0.5f * A * B;  // Площадь треугольного треугольника
}

char* translation(long x) {
    static char buffer[65];
    std::memset(buffer, 0, sizeof(buffer));  // Инициализируем память
    int index = 63;

    if (x == 0) {
        buffer[index] = '0';
        return &buffer[index];
    }

    while (x > 0) {
        buffer[--index] = '0' + (x % 3);
        x /= 3;
    }

    if (index < 0 || index >= 65) {
        std::fprintf(stderr, "Translation error: buffer index out of range\n");
        buffer[0] = '\0';  // Возвращаем пустую строку при ошибке
        return buffer;
    }

    return &buffer[index];
}