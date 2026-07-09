
#include "Server.h"

#include <iostream>
#include <variant>

#include <array>
#include <iostream>
#include <asio.hpp>

using asio::ip::tcp;

int main(int argc, char *argv[])
{
    try
    {
        asio::io_context io_context;
        Server server(io_context);

        io_context.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
