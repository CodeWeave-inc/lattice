#ifndef SERVER_HPP
#define SERVER_HPP
#include <asio.hpp>

#include "AClient.hpp"
#include "../router/Router.hpp"

namespace Lattice {
    class Server {
    protected:
        Router *_router; // Does not own
        bool _running;
        short _port;
        using ClientFactory = std::function<AClient *(asio::ip::tcp::socket *, Router *)>;

        asio::io_context _ioContext;
        asio::ip::tcp::acceptor _acceptor;
        std::vector<AClient *> _clients;
        ClientFactory _clientFactory;

        Server(Router *router, short port, ClientFactory clientFactory);

    public:
        virtual ~Server();

        void start();

        void stop();

        [[nodiscard]] bool isRunning() const;

        [[nodiscard]] short getPort() const;
    };
}

#endif //SERVER_HPP
