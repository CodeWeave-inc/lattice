#ifndef ALATTICEERROR_HPP
#define ALATTICEERROR_HPP

#include <exception>
#include <string>
#include <cpptrace/cpptrace.hpp>

namespace Lattice {
    class ALatticeError : public std::exception {
    protected:
        std::string _message;
        cpptrace::stacktrace _stacktrace;

        explicit ALatticeError(std::string message,
                               cpptrace::stacktrace stacktrace =
                                       cpptrace::generate_trace());

    public:
        ~ALatticeError() override;

        [[nodiscard]] const char *what() const noexcept override;

        [[nodiscard]] cpptrace::stacktrace getStacktrace() const;
    };
}

#endif //ALATTICEERROR_HPP
