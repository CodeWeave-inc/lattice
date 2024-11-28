#ifndef NOTFOUND_HPP
#define NOTFOUND_HPP
#include "AHttpError.hpp"

namespace Lattice::Http {
    class NotFound final : public AHttpError {
    public:
        NotFound();

        ~NotFound() override;
    };
}

#endif //NOTFOUND_HPP
