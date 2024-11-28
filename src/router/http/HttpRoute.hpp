#ifndef HTTPROUTE_HPP
#define HTTPROUTE_HPP
#include "HttpEndpoint.hpp"
#include "HttpMiddleware.hpp"
#include "../IRoute.hpp"
#include "../../messages/http/Response.hpp"

namespace Lattice::Http {
    class HttpRoute final : public IRoute {
    protected:
        std::string _path;
        std::vector<HttpMiddleware *> _middlewares;

        HttpEndpoint *_endpoint;

    public:
        explicit HttpRoute(std::string path);

        ~HttpRoute() override;

        [[nodiscard]] std::string getPath() const;

        void addMiddleware(HttpMiddleware *middleware, int index = -1);

        [[nodiscard]] std::vector<HttpMiddleware *> getMiddlewares() const;

        void setEndpoint(HttpEndpoint *endpoint);

        bool canAccept(IMessage *message) const override;

        Response *handle(IMessage *message) const override;
    };
}

#endif //HTTPROUTE_HPP
