#ifndef HTTPVERSIONNOTSUPPORTED_HPP
#define HTTPVERSIONNOTSUPPORTED_HPP
#include "AHttpError.hpp"

namespace Lattice::Http {
    class HttpVersionNotSupported final : public AHttpError {
    public:
        HttpVersionNotSupported();

        ~HttpVersionNotSupported() override;
    };
}

#endif //HTTPVERSIONNOTSUPPORTED_HPP
