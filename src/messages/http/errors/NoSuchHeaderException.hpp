#ifndef NOSUCHHEADEREXCEPTION_HPP
#define NOSUCHHEADEREXCEPTION_HPP
#include "../../../errors/ALatticeError.hpp"

namespace Lattice::Http {
    class NoSuchHeaderException final : ALatticeError {
    public:
        explicit NoSuchHeaderException(const std::string &headerName);

        ~NoSuchHeaderException() override;
    };
}

#endif //NOSUCHHEADEREXCEPTION_HPP
