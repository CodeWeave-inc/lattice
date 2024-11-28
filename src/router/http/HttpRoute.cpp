#include "HttpRoute.hpp"

#include <sstream>

#include "../../messages/http/Request.hpp"

namespace Lattice::Http {
    HttpRoute::HttpRoute(std::string path) : _path(std::move(path)), _endpoint(nullptr) {
    }

    HttpRoute::~HttpRoute() {
        delete this->_endpoint;
    }

    std::string HttpRoute::getPath() const {
        return this->_path;
    }

    bool HttpRoute::canAccept(IMessage *message) const {
        if (message == nullptr) {
            return false;
        }

        const auto request = dynamic_cast<Request *>(message);

        if (request == nullptr || this->_endpoint == nullptr) {
            return false;
        }

        // Check if the method is allowed
        if (std::find(this->_endpoint->getMethods().begin(),
                      this->_endpoint->getMethods().end(), request->getMethod()) ==
            this->_endpoint->getMethods().end()) {
            return false;
        }
        if (this->_path == "/404") {
            return true;
        }

        // Check if the path matches
        return this->_path == request->getUri(); // TODO Add parameterized paths
    }

    std::vector<HttpMiddleware *> HttpRoute::getMiddlewares() const {
        return this->_middlewares;
    }

    void HttpRoute::addMiddleware(HttpMiddleware *middleware, const int index) {
        if (index == -1) {
            this->_middlewares.push_back(middleware);
        } else {
            this->_middlewares.insert(this->_middlewares.begin() + index, middleware);
        }
    }


    Response *HttpRoute::handle(IMessage *message) const {
        if (!this->canAccept(message)) {
            return new Response({}, {{"message", "Route not found"}}, 404);
        }

        for (const auto &middleware: this->_middlewares) {
            std::variant<Response *, AHttpError *, std::monostate> result = middleware->
                    handle(dynamic_cast<Request *>(message));

            if (std::holds_alternative<Response *>(result)) {
                return std::get<Response *>(result);
            }
            if (std::holds_alternative<AHttpError *>(result)) {
                cpptrace::stacktrace trace = std::get<AHttpError *>(result)->
                        getStacktrace();
                std::ostringstream stream;
                trace.print(stream);
                nlohmann::json body = {
                    {"message", std::get<AHttpError *>(result)->what()}
                };
                if (std::get<AHttpError *>(result)->shouldPrintStackTrace()) {
                    body["stacktrace"] = stream.str();
                }
                return new Response({}, body,
                                    std::get<AHttpError *>(result)->getStatusCode());
            }
        }

        std::variant<Response *, AHttpError *> result = this->_endpoint->handle(
            dynamic_cast<Request *>(message));

        if (std::holds_alternative<Response *>(result)) {
            return std::get<Response *>(result);
        }

        cpptrace::stacktrace trace = std::get<AHttpError *>(result)->getStacktrace();
        std::ostringstream stream;
        trace.print(stream);
        nlohmann::json body = {
            {"message", std::get<AHttpError *>(result)->what()}
        };
        if (std::get<AHttpError *>(result)->shouldPrintStackTrace()) {
            body["stacktrace"] = stream.str();
        }
        return new Response({}, body,
                            std::get<AHttpError *>(result)->getStatusCode());
    }

    void HttpRoute::setEndpoint(HttpEndpoint *endpoint) {
        this->_endpoint = endpoint;
    }
} // Lattice::Http
