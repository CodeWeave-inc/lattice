#include "ALatticeError.hpp"

#ifndef __APPLE__
#include <utility>
#endif

namespace Lattice {
    ALatticeError::ALatticeError(std::string message,
                                 cpptrace::stacktrace stacktrace)
        : _message(std::move(message)), _stacktrace(std::move(stacktrace)) {
    }

    ALatticeError::~ALatticeError() = default;

    const char *ALatticeError::what() const noexcept {
        return this->_message.c_str();
    }

    cpptrace::stacktrace ALatticeError::getStacktrace() const {
        return this->_stacktrace;
    }
}
