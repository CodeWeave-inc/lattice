#include "NotFound.hpp"

namespace Lattice::Http {
    NotFound::NotFound(): AHttpError(404, "Not Found") {
    }

    NotFound::~NotFound() = default;
} // Lattice
