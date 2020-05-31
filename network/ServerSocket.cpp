//
// Created by lezenn on 31/05/2020.
//

#include <iostream>
#include "ServerSocket.h"

network::ServerSocket::ServerSocket(int port)
    : m_port(port)
{
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket == -1) {
        perror("socket()");
        exit(errno);
    }

    sockaddr_in sin;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(m_port);

    int err = bind(m_socket, (sockaddr*)& sin, sizeof(sin));

    if (err == -1) {
        perror("bind()");
        exit(errno);
    }

    err = listen(m_socket, 5);
    if (err == -1) {
        perror("listen()");
        exit(errno);
    }

    std::cout << "Server is listening on port " << std::to_string(m_port) << std::endl;
}

network::ServerSocket::~ServerSocket() {
    close(m_socket);
}

void network::ServerSocket::loop(std::function<bool(int)> func) {
    while(std::cout << "Looping" << std::endl, loopOnce(func));
}

void network::ServerSocket::loop() {
    loop(ServerSocket::defaultCallback);
}

SOCKET network::ServerSocket::get_socket() const {
    return m_socket;
}

int network::ServerSocket::get_port() const {
    return m_port;
}

bool network::ServerSocket::defaultCallback(int socket) {
    std::cout << "Default callback called..." << std::endl;
    return false;
}

bool network::ServerSocket::loopOnce(std::function<bool(int)> func) {
    sockaddr_in csin = {0};
    unsigned int csinsize = sizeof(csin);
    SOCKET sock_tmp = accept(m_socket, (sockaddr*)& csin, &csinsize);
    bool result = false;
    if (sock_tmp != -1) {
        result = func(sock_tmp);
        close(sock_tmp);
    } else {
        perror("accept()");
    }
    return result;
}
