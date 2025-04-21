#ifndef HTTP_HPP
#define HTTP_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <string>

namespace Classic
{
    class Socket
    {
    private:
        int m_sock;
        int m_connection;
        struct sockaddr_in m_address;
    public:
        int connection;
        // construtor
        Socket(int domain, int service, int protocol, int port, u_long IPadrress);
        // virtual function that allows us to connect to a network
        virtual int connect_to_network(int sock, struct sockaddr_in address) = 0;
        // checks the connection
        void check_connection(int);
        // getter function declaratinos
        struct sockaddr_in get_address();
        int get_sock();
        int get_connection();
        // setter fucntion declarations
        void set_connection(int conn);
    };
}

#endif // HTTP_HPP //