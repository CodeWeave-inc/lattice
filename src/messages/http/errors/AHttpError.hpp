#ifndef AHTTPERROR_HPP
#define AHTTPERROR_HPP
#include "../../../errors/ALatticeError.hpp"

namespace Lattice::Http {
    class AHttpError : public ALatticeError {
    protected:
        int _statusCode;
        bool _printStackTrace;

        AHttpError(int statusCode, std::string message, bool printStackTrace = false);

    public:
        ~AHttpError() override;

        [[nodiscard]] int getStatusCode() const;

        [[nodiscard]] bool shouldPrintStackTrace() const;
    };
}

#endif //AHTTPERROR_HPP
