#include "parent.hpp"
#include "child1.hpp"
#include "child2.hpp"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>

void startParentProcess() {
    int pipe1[2], pipe2[2], pipe3[2];
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1 || pipe(pipe3) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid_t child1_pid = fork();
    if (child1_pid == -1) {
        perror("fork failed");
        exit(1);
    }

    if (child1_pid == 0) {
        startChild1(pipe1, pipe3);
        exit(0);
    }

    pid_t child2_pid = fork();
    if (child2_pid == -1) {
        perror("fork failed");
        exit(1);
    }

    if (child2_pid == 0) {
        startChild2(pipe3, pipe2);
        exit(0);
    }

    close(pipe1[0]);
    close(pipe2[1]);
    close(pipe3[0]);

    char input[BUFFER_SIZE];
    char output[BUFFER_SIZE];

    std::cout << "Введите строку: ";
    while (fgets(input, BUFFER_SIZE, stdin)) {
        write(pipe1[1], input, strlen(input) + 1);

        ssize_t n = read(pipe2[0], output, BUFFER_SIZE);
        if (n > 0) {
            std::cout << "Обработанная строка: " << output << std::endl;
        } else {
            break;
        }

        std::cout << "Введите строку: ";
    }

    close(pipe1[1]);
    close(pipe2[0]);

    waitpid(child1_pid, NULL, 0);
    waitpid(child2_pid, NULL, 0);
}