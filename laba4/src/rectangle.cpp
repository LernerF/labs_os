#include "rectangle.h"
#include <cstdio>
#include <cstring>

float Square(float A, float B) {
    return A * B;  // Площадь прямоугольника
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
        buffer[--index] = (x % 2) ? '1' : '0';
        x /= 2;
    }
        
    if (index < 0) {
        std::fprintf(stderr, "Translation error: buffer overflow\n");
        buffer[0] = '\0';  // Возвращаем пустую строку при ошибке
        return buffer;
    }

    return &buffer[index];
}
