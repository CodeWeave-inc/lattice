#ifndef HTTPMIDDLEWARE_HPP
#define HTTPMIDDLEWARE_HPP
#include <variant>

#include "../../messages/http/Request.hpp"
#include "../../messages/http/Response.hpp"
#include "../../messages/http/errors/AHttpError.hpp"

namespace Lattice::Http {
    class HttpMiddleware {
    protected:
        HttpMiddleware();

    public:
        virtual ~HttpMiddleware();

        virtual std::variant<Response *, AHttpError *, std::monostate> handle(
            Request *message) const = 0;
    };
}

#endif //HTTPMIDDLEWARE_HPP
