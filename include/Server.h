#ifndef SERVER_H
#define SERVER_H

#include <asio.hpp>

class Server
{
public:
    Server(asio::io_context &io_context);

private:
    asio::awaitable<void> start_accept();
    asio::awaitable<void> session(asio::ip::tcp::socket socket);
    asio::ip::tcp::acceptor acceptor_;
    asio::io_context &io_context_;
};

#endif // SERVER_H
