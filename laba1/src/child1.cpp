#include "child1.hpp"
#include "utils.hpp"
#include <unistd.h>
#include <cstring>

void startChild1(int pipe1[], int pipe3[]) {
    close(pipe1[1]);
    close(pipe3[0]);

    char buffer[BUFFER_SIZE];
    ssize_t n;

    while ((n = read(pipe1[0], buffer, BUFFER_SIZE)) > 0) {
        buffer[n] = '\0';
        toUpperCase(buffer);
        write(pipe3[1], buffer, strlen(buffer) + 1);
    }

    close(pipe1[0]);
    close(pipe3[1]);
}