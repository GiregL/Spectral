//
// Created by lezenn on 31/05/2020.
//

#ifndef SPECTRAL_SERVERSOCKET_H
#define SPECTRAL_SERVERSOCKET_H

#include <functional>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SOCKET int

namespace network {

    class ServerSocket {
    public:
        explicit ServerSocket(int port);
        ~ServerSocket();

        void loop(std::function<bool(SOCKET)> func);
        void loop();

        // Getters
        SOCKET get_socket() const;
        int get_port() const;

    private:
        bool loopOnce(std::function<bool(SOCKET)> func);

        static bool defaultCallback(SOCKET socket);

        SOCKET m_socket;
        int m_port;
    };
}


#endif //SPECTRAL_SERVERSOCKET_H
