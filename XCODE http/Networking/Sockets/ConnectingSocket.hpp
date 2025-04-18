#ifndef CONNECTING_SOCKET_HPP
#define CONNECTING_SOCKET_HPP

#include <iostream>
#include <sys/socket.h>
#include "ClassicSocket.hpp"

namespace Connecting
{
    class ConnectingSocket : public Classic::Socket
    {
    public:
        ConnectingSocket(int domain, int service, int protocol, int port, u_long interface);
        int connect_to_network(int sock, struct sockaddr_in address);
    };
}

#endif //CONNECTING_SOCKET_HPP//