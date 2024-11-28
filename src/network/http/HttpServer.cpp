#include "HttpServer.hpp"

#include "HttpClient.hpp"

namespace Lattice::Http {
    HttpServer::HttpServer(Router *router, const short port): Server(router, port,
        [](asio::ip::tcp::socket *socket, Router *_router) {
            return new HttpClient(socket, _router);
        }) {
    }

    HttpServer::~HttpServer() = default;
} // Lattice
