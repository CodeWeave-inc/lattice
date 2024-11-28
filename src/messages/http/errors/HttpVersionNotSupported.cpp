#include "HttpVersionNotSupported.hpp"

namespace Lattice::Http {
    HttpVersionNotSupported::HttpVersionNotSupported()
        : AHttpError(505, "HTTP Version Not Supported") {
    }

    HttpVersionNotSupported::~HttpVersionNotSupported() = default;
} // Lattice
