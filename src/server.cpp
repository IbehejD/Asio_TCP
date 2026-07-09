
#include <iostream>
#include <variant>

#include <array>
#include <iostream>
#include <asio.hpp>

using asio::ip::tcp;

void handle_write(std::shared_ptr<std::string> msg, asio::error_code error) {

};

void start_accept(asio::io_context &io_context, tcp::acceptor &acceptor);

void handle_accept(std::shared_ptr<tcp::socket> sock, asio::io_context &io_context, tcp::acceptor &acceptor, asio::error_code error)
{
    std::shared_ptr<std::string> msg = std::make_shared<std::string>("Hello world!\n");
    asio::async_write(*sock, asio::buffer(*msg), std::bind(handle_write, msg, asio::placeholders::error));

    start_accept(io_context, acceptor);
};

void start_accept(asio::io_context &io_context, tcp::acceptor &acceptor)
{
    std::shared_ptr<tcp::socket> socket = std::make_shared<tcp::socket>(io_context);
    acceptor.async_accept(*socket, std::bind(handle_accept, socket, std::ref(io_context), std::ref(acceptor), asio::placeholders::error));
};

int main(int argc, char *argv[])
{
    try
    {
        asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));
        start_accept(io_context, acceptor);

        io_context.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
