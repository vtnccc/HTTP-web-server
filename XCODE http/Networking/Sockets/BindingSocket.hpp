#ifndef BINDING_SOCKET_HPP
#define BINDING_SOCKET_HPP

#include <sys/socket.h>
#include <iostream>
#include "ClassicSocket.hpp"

namespace Binding
{
    class BindingSocket : public Classic::Socket
    {
    public:
        BindingSocket(int domain, int service, int protocol, int port, u_long interface);
        int connect_to_network(int sock, struct sockaddr_in address);
    };
}

#endif //BINDING_SOCKET_HPP//