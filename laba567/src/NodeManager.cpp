#include "NodeManager.h"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <unistd.h> // для fork(), execl()

NodeManager::NodeManager(bool testMode)
    : zmqContext(std::make_unique<zmq::context_t>(1))
    , m_testMode(testMode)
{
}

NodeManager::~NodeManager() {
    // Здесь можно было бы убивать процессы, если бы они были запущены
}

std::string NodeManager::createNode(int id, int parentId) {
    if (nodes.count(id) > 0) {
        return "Error: Already exists";
    }
    if (parentId != -1 && nodes.count(parentId) == 0) {
        return "Error: Parent not found";
    }

    // Если мы в тестовом режиме — просто «симулируем» создание узла
    if (m_testMode) {
        std::string address = "mock://node_" + std::to_string(id);
        nodes[id] = { address, -1 };
        return "Ok: " + address;
    }

    // Иначе — запускаем реальный процесс (ComputeNodeProcess)
    std::string address = "inproc://node_" + std::to_string(id);
    pid_t pid = fork();
    if (pid == 0) {
        // В дочернем процессе
        execl("./ComputeNodeProcess", "./ComputeNodeProcess", address.c_str(), nullptr);
        exit(1); // Если execl не сработал
    }

    // В родительском процессе
    nodes[id] = { address, pid };
    return "Ok: " + address;
}

std::string NodeManager::execCommand(int id, const std::string& text, const std::string& pattern) {
    if (nodes.find(id) == nodes.end()) {
        return "Error: Not found";
    }
    // В тестовом режиме пока что просто возвращаем результат без реального запроса
    // В реальности тут бы мы отправили через ZeroMQ запрос к узлу
    return "Ok:" + std::to_string(id) + ": [" + text + "|" + pattern + "]";
}

void NodeManager::startHeartbit(int interval) {
    if (m_testMode) {
        std::cout << "Mock heartbit started with interval = " << interval << std::endl;
    } else {
        std::cout << "Real heartbit started with interval = " << interval << std::endl;
    }
}

std::string NodeManager::pingNode(int id) {
    if (nodes.find(id) == nodes.end()) {
        return "Error: Not found";
    }
    // Аналогично, в реальном режиме тут был бы запрос через ZeroMQ
    return "Ok: 1";
}