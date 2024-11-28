#ifndef ALCLIENT_HPP
#define ALCLIENT_HPP
#include <asio/ip/tcp.hpp>

#include "../router/Router.hpp"

namespace Lattice {
    class AClient {
        void read();

    protected:
        asio::ip::tcp::socket *_socket;
        Router *_router; // Does not own

        AClient(asio::ip::tcp::socket *socket, Router *router);

        virtual void beforeClose();

    public:
        virtual ~AClient();

        [[nodiscard]] asio::ip::tcp::socket *getSocket() const;

        [[nodiscard]] Router *getRouter() const;

        virtual void handleRead(const asio::error_code &error,
                                std::size_t bytesTransferred,
                                std::string data) = 0;

        virtual void handleWrite(const asio::error_code &error,
                                 std::size_t bytesTransferred) = 0;

        void close();

        void write(std::string data);
    };
}
#endif //ACLIENT_HPP
