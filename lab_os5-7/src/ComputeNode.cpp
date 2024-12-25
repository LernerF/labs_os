#include "ComputeNode.h"
#include <iostream>

ComputeNode::ComputeNode(int id, std::shared_ptr<zmq::context_t> context)
    : id(id), socket(*context, ZMQ_REP), running(true)
{
    std::string address = "inproc://node_" + std::to_string(id);
    socket.connect(address);
}

void ComputeNode::run() {
    while (running) {
        zmq::message_t request;
        auto result = socket.recv(request, zmq::recv_flags::none);
        if (!result) {
            continue; // Тайм-аут или отсутствие данных
        }

        std::string message = request.to_string();
        std::string response;

        if (message.find(';') != std::string::npos) {
            auto delimiter = message.find(';');
            std::string text = message.substr(0, delimiter);
            std::string pattern = message.substr(delimiter + 1);

            size_t pos = 0;
            std::string positions;
            while ((pos = text.find(pattern, pos)) != std::string::npos) {
                positions += std::to_string(pos) + ";";
                pos += pattern.length();
            }

            response = positions.empty() ? "-1" : positions;
        } 
        else if (message == "ping") {
            response = "pong";
        } 
        else {
            response = "unknown";
        }

        socket.send(zmq::buffer(response), zmq::send_flags::none);
    }
}

void ComputeNode::stop() {
    running = false;
}