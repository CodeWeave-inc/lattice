#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP
#include "../Server.hpp"

namespace Lattice::Http {
    class HttpServer final : public Server {
    public:
        HttpServer(Router *router, short port);

        ~HttpServer() override;
    };
}


#endif //HTTPSERVER_HPP
