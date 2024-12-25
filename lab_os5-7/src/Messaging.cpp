#include "Messaging.h"
#include <stdexcept>

void Messaging::sendMessage(zmq::socket_t& socket, const std::string& message) {
    zmq::message_t zmqMessage(message.size());
    memcpy(zmqMessage.data(), message.data(), message.size());
    socket.send(zmqMessage, zmq::send_flags::none);
}

std::string Messaging::receiveMessage(zmq::socket_t& socket) {
    zmq::message_t zmqMessage;
    auto result = socket.recv(zmqMessage, zmq::recv_flags::none);
    if (!result) {
        throw std::runtime_error("Failed to receive message");
    }
    return std::string(static_cast<char*>(zmqMessage.data()), zmqMessage.size());
}