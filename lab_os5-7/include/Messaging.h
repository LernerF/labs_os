#ifndef MESSAGING_H
#define MESSAGING_H

#include <zmq.hpp>
#include <string>

class Messaging {
public:
    static void sendMessage(zmq::socket_t& socket, const std::string& message);
    static std::string receiveMessage(zmq::socket_t& socket);
};

#endif // MESSAGING_H