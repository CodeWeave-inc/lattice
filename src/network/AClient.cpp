#include "AClient.hpp"

#include <asio/read.hpp>
#include <asio/write.hpp>
#include <spdlog/spdlog.h>

namespace Lattice {
    AClient::AClient(asio::ip::tcp::socket *socket,
                     Router *router): _socket(socket),
                                      _router(router) {
        this->_socket->non_blocking(true);
        this->read();
    }

    AClient::~AClient() {
        if (this->_socket->is_open()) {
            this->close();
        }
    }

    asio::ip::tcp::socket *AClient::getSocket() const {
        return this->_socket;
    }

    void AClient::beforeClose() {
    }

    void AClient::close() {
        if (!this->_socket->is_open()) {
            return;
        }
        spdlog::info("Closing connection from {}",
                     this->_socket->remote_endpoint().address().to_string());
        this->beforeClose();
        this->_socket->close();
    }

    void AClient::write(std::string data) {
        asio::async_write(*this->_socket, asio::buffer(data),
                          [this](const asio::error_code &error,
                                 const std::size_t bytesTransferred) {
                              this->handleWrite(error, bytesTransferred);
                          });
    }

    void AClient::read() {
        std::vector<char> data(1024);

        this->_socket->async_receive(asio::buffer(data),
                                     [this, data](const asio::error_code &error,
                                                  const std::size_t
                                                  bytesTransferred) {
                                         const std::string dataStr(data.begin(),
                                             data.begin() +
                                             bytesTransferred);
                                         this->handleRead(
                                             error, bytesTransferred, dataStr);
                                         this->read();
                                     });
    }

    Router *AClient::getRouter() const {
        return this->_router;
    }
} // Lattice
