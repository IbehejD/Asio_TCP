#include "Server.h"

using asio::ip::tcp;

Server::Server(asio::io_context &io_context) : io_context_(io_context), acceptor_(io_context, tcp::endpoint(tcp::v4(), 13))
{
    co_spawn(io_context_, start_accept(), asio::detached);
}

asio::awaitable<void> Server::session(tcp::socket socket)
{
    std::string msg = "Hello world!\n";
    co_await asio::async_write(socket, asio::buffer(msg), asio::use_awaitable);
};

asio::awaitable<void> Server::start_accept()
{
    for (;;)
    {
        tcp::socket socket = co_await acceptor_.async_accept(asio::use_awaitable);
        co_spawn(io_context_, session(std::move(socket)), asio::detached);
    };
}