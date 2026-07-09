
#include "Client.h"

#include <iostream>
#include <variant>

#include <array>
#include <iostream>
#include <asio.hpp>

using asio::ip::tcp;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: client <host>" << std::endl;
        return 1;
    }

    const char *ip = argv[1];
    const char *port = argv[2];

    try
    {
        asio::io_context io_context;
        Client client(io_context, ip, port);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}