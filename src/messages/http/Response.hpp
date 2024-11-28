#ifndef RESPONSE_HPP
#define RESPONSE_HPP
#include "AbstractHttpMessage.hpp"

namespace Lattice::Http {
    class Response final : public AbstractHttpMessage {
    protected:
        unsigned short _statusCode;

    public:
        explicit Response(const std::vector<Header> &headers = {},
                          const std::string &body = "", unsigned short statusCode = 200);


        explicit Response(const std::vector<Header> &headers = {},
                          const json &body = {}, unsigned short statusCode = 200);

        ~Response() override;

        [[nodiscard]] unsigned short getStatusCode() const;

        void setStatusCode(unsigned short statusCode);

        static std::string reasonFromStatus(unsigned short statusCode);

        [[nodiscard]] std::string toString() const override;

        void fromString(const std::string &string) override;
    };
}

#endif //RESPONSE_HPP
