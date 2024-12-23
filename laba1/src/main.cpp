#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include "parent.hpp"

int main() {
    startParentProcess();
    return 0;
}