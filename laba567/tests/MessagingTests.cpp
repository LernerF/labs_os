#include "Messaging.h"
#include <gtest/gtest.h>
#include <zmq.hpp>

TEST(MessagingTests, SendMessage) {
    zmq::context_t context(1);
    zmq::socket_t sender(context, zmq::socket_type::pair);
    zmq::socket_t receiver(context, zmq::socket_type::pair);

    sender.bind("inproc://test_messaging");
    receiver.connect("inproc://test_messaging");

    std::string message = "Hello, Node!";
    Messaging::sendMessage(sender, message);

    std::string receivedMessage = Messaging::receiveMessage(receiver);
    EXPECT_EQ(receivedMessage, message) 
        << "Message mismatch. Expected: " << message 
        << ", Received: " << receivedMessage;
}

TEST(MessagingTests, ReceiveMessage) {
    zmq::context_t context(1);
    zmq::socket_t sender(context, zmq::socket_type::pair);
    zmq::socket_t receiver(context, zmq::socket_type::pair);

    sender.bind("inproc://test_messaging");
    receiver.connect("inproc://test_messaging");

    std::string message = "Node Acknowledged";
    Messaging::sendMessage(sender, message);

    std::string receivedMessage = Messaging::receiveMessage(receiver);
    EXPECT_EQ(receivedMessage, message) 
        << "Message mismatch. Expected: " << message 
        << ", Received: " << receivedMessage;
}