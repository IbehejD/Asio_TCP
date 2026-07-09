#ifndef CLIENT_H
#define CLIENT_H

#include <asio.hpp>

class Client
{
public:
    Client(asio::io_context &io_context, const char *ip, const char *port);
    void connect();
    void read();
    void resolve_ip(const char *ip, const char *port);

private:
    asio::io_context &io_context_;
    asio::ip::tcp::resolver::results_type endpoints_;
    asio::ip::tcp::socket socket_;
};

#endif // CLIENT_H
