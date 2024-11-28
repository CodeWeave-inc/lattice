#ifndef NOSUCHQUERYEXCEPTION_HPP
#define NOSUCHQUERYEXCEPTION_HPP
#include "../../../errors/ALatticeError.hpp"

namespace Lattice::Http {
    class NoSuchQueryException final : public ALatticeError {
    public:
        explicit NoSuchQueryException(const std::string &queryName);

        ~NoSuchQueryException() override;
    };
} // Lattice

#endif //NOSUCHQUERYEXCEPTION_HPP
