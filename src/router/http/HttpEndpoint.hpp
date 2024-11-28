#ifndef HTTPENDPOINT_HPP
#define HTTPENDPOINT_HPP
#include <variant>

#include "../../messages/http/Request.hpp"
#include "../../messages/http/errors/AHttpError.hpp"

namespace Lattice::Http {
    class Response;

    class HttpEndpoint {
    protected:
        std::vector<Method> _methods;

        explicit HttpEndpoint(Method method, std::vector<Method> methods = {});

    public:
        virtual ~HttpEndpoint();

        [[nodiscard]] std::vector<Method> getMethods() const;

        virtual std::variant<Response *, AHttpError *> handle(Request *request) = 0;
    };
}

#endif //HTTPENDPOINT_HPP
