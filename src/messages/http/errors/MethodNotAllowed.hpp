#ifndef METHODNOTALLOWED_HPP
#define METHODNOTALLOWED_HPP
#include "AHttpError.hpp"

namespace Lattice::Http {
    class MethodNotAllowed final : public AHttpError {
    public:
        MethodNotAllowed();

        ~MethodNotAllowed() override;
    };
}

#endif //METHODNOTALLOWED_HPP
