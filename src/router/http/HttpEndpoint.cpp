#include "HttpEndpoint.hpp"

namespace Lattice::Http {
    HttpEndpoint::HttpEndpoint(const Method method, std::vector<Method> methods) {
        this->_methods.push_back(method);
        for (const auto &m: methods) {
            this->_methods.push_back(m);
        }
    }

    HttpEndpoint::~HttpEndpoint() = default;

    std::vector<Method> HttpEndpoint::getMethods() const {
        return this->_methods;
    }
} // Lattice::Http
