#include "NoSuchHeaderException.hpp"

namespace Lattice::Http {
    NoSuchHeaderException::NoSuchHeaderException(
        const std::string &headerName): ALatticeError(
        "No such header: " + headerName) {
    }

    NoSuchHeaderException::~NoSuchHeaderException() = default;
}
