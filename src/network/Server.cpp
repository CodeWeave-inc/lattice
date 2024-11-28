#include "Server.hpp"

#include <spdlog/spdlog.h>
#ifndef __APPLE__
#include <utility>
#endif

namespace Lattice {
    Server::Server(Router *router, const short port,
                   ClientFactory clientFactory): _router(router), _running(false),
                                                 _port(port), _acceptor(
                                                     this->_ioContext,
                                                     asio::ip::tcp::endpoint(
                                                         asio::ip::tcp::v4(),
                                                         this->_port)),
                                                 _clientFactory(
                                                     std::move(clientFactory)) {
    }

    Server::~Server() = default;

    void Server::start() {
        this->_acceptor.listen();
        if (!this->_running) {
            spdlog::info("Starting server on port {}", this->_port);
        }
        this->_running = true;

        // Create a new socket
        auto socket = new asio::ip::tcp::socket(this->_ioContext);

        // Accept async connections
        this->_acceptor.async_accept(*socket,
                                     [this, &socket](
                                 const asio::error_code &error) {
                                         if (!error) {
                                             AClient *client = this->_clientFactory(
                                                 socket,
                                                 this->_router);
                                             this->_clients.push_back(client);
                                             spdlog::info(
                                                 "Accepted connection from {}",
                                                 socket->remote_endpoint().address().
                                                 to_string());
                                         } else {
                                             spdlog::error(
                                                 "Error accepting connection: {}",
                                                 error.message());
                                         }

                                         // Continue accepting connections
                                         if (this->_running) {
                                             this->start();
                                         }
                                     });

        this->_ioContext.run();
    }

    void Server::stop() {
        this->_acceptor.close();
        this->_running = false;

        for (const auto client: this->_clients) {
            client->close();
            delete client;
        }
        this->_clients.clear();
    }

    bool Server::isRunning() const {
        return this->_running;
    }

    short Server::getPort() const {
        return this->_port;
    }
} // Lattice
