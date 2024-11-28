#ifndef HTTPCLIENT_HPP
#define HTTPCLIENT_HPP
#include "../AClient.hpp"


namespace Lattice::Http {
    class HttpClient final : public AClient {
    public:
        HttpClient(asio::ip::tcp::socket *socket,
                   Router *router);

        ~HttpClient() override;

        void handleRead(const asio::error_code &error,
                        std::size_t bytesTransferred, std::string data) override;

        void handleWrite(const asio::error_code &error,
                         std::size_t bytesTransferred) override;
    };
}

#endif //HTTPCLIENT_HPP
