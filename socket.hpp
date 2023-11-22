// server.hpp
#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
// local header

class SocketServer {
  private:
    sockaddr_in server = {};
    int server_socket;

  public:
    SocketServer() {}

    void init(char *arg_port, char *arg_ipaddress) {
        server_socket = socket(AF_INET, SOCK_STREAM, 0);

        if (server_socket == -1) {
            std::cerr << "socket is fail " << std::endl;
            exit(0);
        }
        std::cout << "Socket server is online!\n";

        int port = atoi(arg_port);
        server.sin_family = AF_INET;
        server.sin_port = htons(port);
        inet_pton(server_socket, arg_ipaddress, &server.sin_addr);
    }

    void bind_and_listen() {
        if (bind(server_socket, (struct sockaddr *)&server, sizeof(struct sockaddr_in)) == -1) {
            std::cerr << "bind is fail " << std::endl;
            exit(0);
        }
        std::cout << "Socket bind complete!\n";

        if (listen(server_socket, 5) == -1) {
            std::cerr << "listen is fail " << std::endl;
            exit(0);
        }
        std::cout << "Socket listen complete!\n";
    }

    bool accept_server(SocketServer &client) {
        socklen_t clientAddressLength = sizeof(client.server);

        client.server_socket = accept(server_socket, (struct sockaddr *)&client.server, &clientAddressLength);

        if (client.server_socket == -1) {
            std::cerr << "accept is fail: " << std::endl;
            exit(0);
        }

        return true;
    }

    int get_socket() const {
        return server_socket;
    }

    void exit_socket() {
        close(server_socket);
    }
};

#endif    // SOCKET_HPP
