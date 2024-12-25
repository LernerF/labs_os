#ifndef COMPUTENODE_H
#define COMPUTENODE_H

#include <zmq.hpp>
#include <atomic>
#include <memory>

class ComputeNode {
public:
    ComputeNode(int id, std::shared_ptr<zmq::context_t> context);
    void run();
    void stop();

private:
    int id;
    zmq::socket_t socket;
    std::atomic<bool> running;
};

#endif // COMPUTENODE_H