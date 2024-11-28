#include "NoSuchQueryException.hpp"

namespace Lattice::Http {
    NoSuchQueryException::NoSuchQueryException(
        const std::string &queryName): ALatticeError(
        "No such query: " + queryName) {
    }

    NoSuchQueryException::~NoSuchQueryException() = default;
} // Lattice
