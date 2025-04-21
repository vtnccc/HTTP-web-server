#include "BindingSocket.hpp"


Binding::BindingSocket::BindingSocket(int domain, int service, int protocol, int port, u_long interface) 
: Socket(domain, service, protocol, port, interface)
{
    set_connection(connect_to_network(get_sock(), get_address()));
    check_connection(get_connection());
}

int Binding::BindingSocket::connect_to_network(int sock, struct sockaddr_in address)
{
    return bind(get_connection(), (struct sockaddr*) &address, sizeof(address));
}
