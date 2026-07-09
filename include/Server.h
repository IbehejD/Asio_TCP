#ifndef SERVER_H
#define SERVER_H

#include <asio.hpp>

class ServerConnection : public std::enable_shared_from_this<ServerConnection>
{
public:
    ServerConnection(asio::io_context &io_context);
    void write(asio::error_code error);
    void handle_write(std::shared_ptr<std::string> msg, asio::error_code error);
    asio::ip::tcp::socket &getSocket();

private:
    asio::ip::tcp::socket socket_;
};

class Server
{
public:
    Server(asio::io_context &io_context);
    void start_accept();

private:
    void handle_accept(std::shared_ptr<ServerConnection>, asio::error_code error);
    asio::ip::tcp::acceptor acceptor_;
    asio::io_context &io_context_;
};

#endif // SERVER_H
