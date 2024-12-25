#ifndef NODE_MANAGER_H
#define NODE_MANAGER_H

#include <string>
#include <unordered_map>
#include <memory>
#include <sys/types.h>
#include <zmq.hpp>

class NodeManager {
public:
    // testMode = true -> не форкаем процессы, имитируем узлы
    explicit NodeManager(bool testMode = false); 
    ~NodeManager();

    std::string createNode(int id, int parentId);
    std::string execCommand(int id, const std::string& text, const std::string& pattern);
    void startHeartbit(int interval);
    std::string pingNode(int id);

private:
    struct NodeInfo {
        std::string address;
        pid_t pid;
    };

    std::unordered_map<int, NodeInfo> nodes;
    std::unique_ptr<zmq::context_t> zmqContext;

    bool m_testMode; 
};

#endif // NODE_MANAGER_H