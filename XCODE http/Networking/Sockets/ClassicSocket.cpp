//
//  HTTP.cpp
//  HTTP server
//
//  Created by vtnc on 10.04.2025.
//

#include "ClassicSocket.hpp"

// default constructor to create a socket and establish a connection
Classic::Socket::Socket(int domain, int service, int protocol, int port, u_long IPadrress)
{
    // define address structure
    m_address.sin_family = domain;
    m_address.sin_port = htons(port);
    m_address.sin_addr.s_addr = htonl(IPadrress);
    // establish connection
    m_sock = socket(domain, service, protocol);
    check_connection(m_sock);
}

// tests the connection
void Classic::Socket::check_connection(int stuff_to_test)
{
    // confirms that both the socket and the connection has been properly established
    // if not the program exits
    if (stuff_to_test < 0)
    {
        std::cerr << "Error connecting..." << std::endl;
        exit(EXIT_FAILURE);
    }
}

// getter functions
//just return the current value assigned to the variable
sockaddr_in Classic::Socket::get_address()
{
    return m_address;
}

int Classic::Socket::get_sock()
{
    return m_sock;
}

int Classic::Socket::get_connection()
{
    return m_connection;
}

void Classic::Socket::set_connection(int conn)
{
    connection = conn;
}
