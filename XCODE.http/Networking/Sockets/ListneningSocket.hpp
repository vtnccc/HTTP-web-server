#ifndef LISTNENING_SOCKET_HPP
#define LISTNENING_SOCKET_HPP

#include "BindingSocket.hpp"
#include <iostream>

namespace Listnening
{
    class ListneningSocket : public Binding::BindingSocket
    {
    private:
        int m_backlog;
        int listnening;
    public:
        ListneningSocket(int domain, int service, int protocol, int port, u_long interface, int bklg);
        void start_listnening();
    };
}

#endif
