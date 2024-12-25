#include <iostream>
#include <string>
#include "NodeManager.h"

int main() {
    NodeManager manager; // testMode = false по умолчанию
    std::string command;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command == "exit") {
            break;
        }

        if (command.rfind("create", 0) == 0) {
            int id, parentId = -1;
            sscanf(command.c_str(), "create %d %d", &id, &parentId);
            std::cout << manager.createNode(id, parentId) << std::endl;
        } 
        else if (command.rfind("exec", 0) == 0) {
            int id;
            std::string text, pattern;
            sscanf(command.c_str(), "exec %d", &id);

            std::cout << "Enter text string: ";
            std::getline(std::cin, text);
            std::cout << "Enter pattern string: ";
            std::getline(std::cin, pattern);

            std::cout << manager.execCommand(id, text, pattern) << std::endl;
        } 
        else if (command.rfind("heartbit", 0) == 0) {
            int interval;
            sscanf(command.c_str(), "heartbit %d", &interval);
            manager.startHeartbit(interval);
            std::cout << "Ok" << std::endl;
        } 
        else if (command.rfind("ping", 0) == 0) {
            int id;
            sscanf(command.c_str(), "ping %d", &id);
            std::cout << manager.pingNode(id) << std::endl;
        } 
        else {
            std::cout << "Unknown command" << std::endl;
        }
    }

    return 0;
}