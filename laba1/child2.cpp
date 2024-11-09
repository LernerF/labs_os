#include "child2.hpp"
#include "utils.hpp"
#include <unistd.h>
#include <cstring>

void startChild2(int pipe3[], int pipe2[]) {
    close(pipe3[1]);  // Закрываем конец записи pipe3
    close(pipe2[0]);  // Закрываем конец чтения pipe2

    char buffer[BUFFER_SIZE];
    ssize_t n;

    while ((n = read(pipe3[0], buffer, BUFFER_SIZE)) > 0) {
        buffer[n] = '\0';
        removeDoubleSpaces(buffer);  // Удаление двойных пробелов
        write(pipe2[1], buffer, strlen(buffer) + 1);  // Передача в pipe2
    }

    close(pipe3[0]);
    close(pipe2[1]);
}