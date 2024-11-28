#include "AHttpError.hpp"

namespace Lattice::Http {
    AHttpError::AHttpError(const int statusCode, std::string message,
                           const bool printStackTrace)
        : ALatticeError(std::move(message)), _statusCode(statusCode),
          _printStackTrace(printStackTrace) {
    }

    AHttpError::~AHttpError() = default;

    int AHttpError::getStatusCode() const {
        return this->_statusCode;
    }

    bool AHttpError::shouldPrintStackTrace() const {
        return this->_printStackTrace;
    }
} // Lattice
