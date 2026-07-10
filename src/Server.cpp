#include "Server.h"

using asio::ip::tcp;

ServerConnection::ServerConnection(asio::io_context &io_context) : socket_(io_context) {};

tcp::socket &ServerConnection::getSocket()
{
    return socket_;
};

void ServerConnection::write(asio::error_code error)
{
    std::shared_ptr<std::string> msg = std::make_shared<std::string>("Hello world!\n");
    asio::async_write(socket_, asio::buffer(*msg), std::bind(&ServerConnection::handle_write, shared_from_this(), msg, asio::placeholders::error));
};

void ServerConnection::handle_write(std::shared_ptr<std::string> msg, asio::error_code error) {

};

void Server::handle_accept(std::shared_ptr<ServerConnection> connection, asio::error_code error)
{
    connection->write(error);
    start_accept();
};

Server::Server(asio::io_context &io_context) : io_context_(io_context), acceptor_(io_context, tcp::endpoint(tcp::v4(), 13))
{
    start_accept();
}

void Server::start_accept()
{
    std::shared_ptr<ServerConnection> connection = std::make_shared<ServerConnection>(io_context_);
    acceptor_.async_accept(connection->getSocket(), std::bind(&Server::handle_accept, this, connection, asio::placeholders::error));
};