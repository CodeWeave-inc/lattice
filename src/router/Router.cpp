#include "Router.hpp"

namespace Lattice {
    Router::Router() = default;

    Router::~Router() {
        for (auto &[id, route]: this->_routes) {
            delete route;
        }
    }

    const IRoute *Router::getRoute(const int id) const {
        if (this->_routes.find(id) == this->_routes.end()) {
            return nullptr;
        }
        return this->_routes.at(id);
    }

    void Router::removeRoute(const int id) {
        if (this->_routes.find(id) != this->_routes.end()) {
            delete this->_routes.at(id);
            this->_routes.erase(id);
        }
    }

    int Router::addRoute(IRoute *route) {
        static int id = 0;
        this->_routes[id] = route;
        return id++;
    }

    IMessage *Router::route(IMessage *message) const {
        for (const auto &[id, route]: this->_routes) {
            if (route->canAccept(message)) {
                return route->handle(message);
            }
        }
        if (this->_notFoundRoute == nullptr) {
            return nullptr;
        }
        if (this->_notFoundRoute->canAccept(message)) {
            return this->_notFoundRoute->handle(message);
        }
        return nullptr;
    }

    void Router::setNotFoundRoute(IRoute *route) {
        this->_notFoundRoute = route;
    }
}
