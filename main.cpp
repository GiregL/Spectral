#include <iostream>
#include "network/ServerSocket.h"
#include <thread>

bool printRequest(int socket)
{
    std::thread([socket]{
        std::string reception;
        for (;;)
        {
            char buffer[512];
            int ret = recv(socket, buffer, 511, 0);
            std::cout << "Lu : " << std::to_string(ret) << std::endl;
            if (ret == -1)
            {
                perror("");
                break;
            }
            if (ret == 0)
            {
                break;
            }
            reception.append(buffer, ret);
        }
        std::cout << "Message received : \n" << reception << "\nEOF" << std::endl;
        close(socket);
    }).detach();
    return true;
}

int main()
{

    network::ServerSocket server(4789);
    server.loop(printRequest);

}
