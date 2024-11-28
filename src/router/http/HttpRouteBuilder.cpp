#include "HttpRouteBuilder.hpp"

namespace Lattice::Http {
    HttpRouteBuilder::HttpRouteBuilder(std::string path): _path(std::move(path)) {
    }

    HttpRouteBuilder::~HttpRouteBuilder() = default;

    HttpRouteBuilder &HttpRouteBuilder::addMiddleware(HttpMiddleware *middleware,
                                                      const int index) {
        if (index == -1) {
            this->_middlewares.push_back(middleware);
        } else {
            this->_middlewares.insert(this->_middlewares.begin() + index, middleware);
        }
        return *this;
    }

    HttpRouteBuilder &HttpRouteBuilder::addMiddleware(
        const std::vector<HttpMiddleware *> &middlewares, const int index) {
        if (index == -1) {
            this->_middlewares.insert(this->_middlewares.end(), middlewares.begin(),
                                      middlewares.end());
        } else {
            this->_middlewares.insert(this->_middlewares.begin() + index,
                                      middlewares.begin(), middlewares.end());
        }
        return *this;
    }

    HttpRoute *HttpRouteBuilder::build(HttpEndpoint *endpoint) const {
        const auto route = new HttpRoute(this->_path);
        for (const auto middleware: this->_middlewares) {
            route->addMiddleware(middleware);
        }
        route->setEndpoint(endpoint);
        return route;
    }
} // Lattice::Http
