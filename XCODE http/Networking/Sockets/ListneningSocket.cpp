#include "ListneningSocket.hpp"

Listnening::ListneningSocket::ListneningSocket(int domain, int service, int protocol, int port, u_long interface, int bklg)
: BindingSocket(domain, service, protocol, port, interface)
{
    m_backlog = bklg;
    start_listnening();
    check_connection(listnening);
}

void Listnening::ListneningSocket::start_listnening()
{
    listnening = listen(get_connection(), m_backlog);
}
