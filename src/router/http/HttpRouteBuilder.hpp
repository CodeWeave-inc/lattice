#ifndef ROUTEBUILDER_HPP
#define ROUTEBUILDER_HPP
#include <string>

#include "HttpEndpoint.hpp"
#include "HttpMiddleware.hpp"
#include "HttpRoute.hpp"

namespace Lattice::Http {
    class HttpRouteBuilder {
    protected:
        std::string _path;
        std::vector<HttpMiddleware *> _middlewares;

    public:
        explicit HttpRouteBuilder(std::string path);

        ~HttpRouteBuilder();

        HttpRouteBuilder &addMiddleware(HttpMiddleware *middleware, int index = -1);

        HttpRouteBuilder &addMiddleware(const std::vector<HttpMiddleware *> &middlewares,
                                        int index = -1);

        HttpRoute *build(HttpEndpoint *endpoint) const;
    };
}

#endif //ROUTEBUILDER_HPP
