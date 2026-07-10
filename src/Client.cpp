#include "Client.h"

#include <array>
#include <iostream>

using asio::ip::tcp;

Client::Client(asio::io_context &io_context, const char *ip, const char *port)
    : io_context_(io_context),
      socket_(io_context)
{
    resolve_ip(ip, port);
    connect();
    read();
}

void Client::resolve_ip(const char *ip, const char *port)
{
    tcp::resolver resolver(io_context_);
    endpoints_ = resolver.resolve(ip, port);
}

void Client::connect()
{
    asio::connect(socket_, endpoints_);
    std::cout << "Connected to " << socket_.remote_endpoint() << std::endl;
}

void Client::read()
{
    for (;;)
    {
        std::array<char, 128> buf;
        asio::error_code error;

        std::size_t len = socket_.read_some(asio::buffer(buf), error);

        if (error == asio::error::eof)
        {
            std::cout << "Connection closed by peer" << std::endl;
            break;
        }
        else if (error)
        {
            throw std::system_error(error);
        }

        std::cout.write(buf.data(), len);
    }
}
