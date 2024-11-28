#include "MethodNotAllowed.hpp"

namespace Lattice::Http {
    MethodNotAllowed::MethodNotAllowed()
        : AHttpError(405, "Method Not Allowed") {
    }

    MethodNotAllowed::~MethodNotAllowed() = default;
} // Lattice
