#include <iostream>
#include "network/ServerSocket.h"
#include <thread>

#include "http/HTTPParser.h"

bool printRequest(int socket)
{
    std::thread([socket]{
        std::string reception;
        char buffer[512];
        int ret = 0;
        while ((ret = recv(socket, buffer, 511, 0)) >= 1)
        {
            std::cout << "Lu : " << std::to_string(ret) << std::endl;
            if (ret == -1)
            {
                perror("Recv()");
                break;
            }
            reception.append(buffer, ret);
        }
        queries::HTTPParser request(reception);
        std::cout << request.to_string() << std::endl;
        close(socket);
    }).detach();
    return true;
}

int main()
{

    network::ServerSocket server(4789);
    server.loop(printRequest);

}
