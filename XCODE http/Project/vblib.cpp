#include "vblib.hpp"
#include <iostream>

int main()
{
    std::cout << "Starting the server..." << std::endl;
    std::cout << "Creating the binding socket..." << std::endl;
    Binding::BindingSocket bs = Binding::BindingSocket(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY);
    std::cout << "Creating the listnening socket..." << std::endl;
    Listnening::ListneningSocket ls = Listnening::ListneningSocket(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 30);
    std::cout << "Success creating the sockets!" << std::endl;
            
    // Get and print the socket properties
    std::cout << "Socket descriptor: " << bs.get_sock() << std::endl;
    std::cout << "Connection status: " << bs.get_connection() << std::endl;
        
    // Get the address structure
    sockaddr_in address = bs.get_address();
    std::cout << "Address family: " << address.sin_family << std::endl;
    std::cout << "Port: " << ntohs(address.sin_port) << std::endl;
    std::cout << "IP Address: " << ntohl(address.sin_addr.s_addr) << std::endl;
}
