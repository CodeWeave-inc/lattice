#include "HttpClient.hpp"

#include <spdlog/spdlog.h>

#include "../../messages/http/Request.hpp"
#include "../../messages/http/Response.hpp"
#include "../../messages/http/errors/AHttpError.hpp"

namespace Lattice::Http {
    HttpClient::HttpClient(asio::ip::tcp::socket *socket,
                           Router *router): AClient(socket, router) {
    }

    HttpClient::~HttpClient() = default;

    void HttpClient::handleRead(const asio::error_code &error,
                                const std::size_t bytesTransferred,
                                const std::string data) {
        if (error) {
            this->close();
            return;
        }
        if (bytesTransferred == 0) {
            return;
        }

        spdlog::info("Received {} bytes", bytesTransferred);

        try {
            auto request = Request(Method::GET, {}, std::string(""));
            request.fromString(data);

            const IMessage *response = this->_router->route(&request);

            if (response != nullptr) {
                this->write(response->getContent());
            }
        } catch (const AHttpError &http_error) {
            std::ostringstream stream;
            stream << http_error.getStacktrace() << std::endl;
            nlohmann::json body = {
                {
                    "message",
                    http_error.what()
                }
            };
            if (http_error.shouldPrintStackTrace()) {
                body["stacktrace"] = stream.str();
            }
            auto res = new Response({}, body,
                                    http_error.getStatusCode());
            return this->write(res->toString());
        } catch (const std::exception &exception) {
            auto res = new Response({}, {
                                        {
                                            "message",
                                            exception.what()
                                        }
                                    },
                                    500);
            return this->write(res->toString());
        }
    }

    void HttpClient::handleWrite(const asio::error_code &error,
                                 const std::size_t bytesTransferred) {
        if (error) {
            spdlog::error("Error writing to socket: {}", error.message());
            this->close();
            return;
        }
        spdlog::info("Wrote {} bytes", bytesTransferred);
        this->close(); // Update for http/2
    }
}
