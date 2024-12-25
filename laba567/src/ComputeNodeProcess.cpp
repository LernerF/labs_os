#include <zmq.hpp>
#include <string>
#include <iostream>

static void runNode(const std::string& address) {
    zmq::context_t context(1);
    zmq::socket_t socket(context, zmq::socket_type::rep);
    socket.connect(address);

    while (true) {
        zmq::message_t request;
        if (!socket.recv(request, zmq::recv_flags::none)) {
            // Если не удалось получить сообщение - прерываем цикл
            // (или можно continue, в зависимости от логики)
            break;
        }

        std::string received = request.to_string();
        size_t delimiter = received.find(';');
        if (delimiter == std::string::npos) {
            // Допустим, если "ping" — отвечаем "pong"
            if (received == "ping") {
                zmq::message_t reply("pong");
                socket.send(reply, zmq::send_flags::none);
            } else {
                // Иначе сообщаем неизвестную команду
                zmq::message_t reply("unknown");
                socket.send(reply, zmq::send_flags::none);
            }
            continue;
        }

        std::string text = received.substr(0, delimiter);
        std::string pattern = received.substr(delimiter + 1);

        size_t pos = 0;
        std::string result;
        while ((pos = text.find(pattern, pos)) != std::string::npos) {
            result += std::to_string(pos) + ";";
            pos += pattern.size();
        }

        if (result.empty()) {
            result = "-1";
        }

        zmq::message_t reply(result);
        socket.send(reply, zmq::send_flags::none);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ComputeNodeProcess <address>" << std::endl;
        return 1;
    }

    runNode(argv[1]);
    return 0;
}