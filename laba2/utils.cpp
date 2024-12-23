#include "utils.hpp"
#include <cctype>
#include <cstring>

void toUpperCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(static_cast<unsigned char>(str[i]));
    }
}

void removeDoubleSpaces(char *str) {
    char *dst = str;
    bool space_found = false;

    for (char *src = str; *src; src++) {
        if (*src == ' ') {
            if (!space_found) {
                *dst++ = *src; // Сохраняем первый пробел
            }
            space_found = true;
        } else {
            *dst++ = *src; // Сохраняем символ
            space_found = false;
        }
    }

    *dst = '\0'; // Завершаем строку
}