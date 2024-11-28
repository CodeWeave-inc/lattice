#include "AbstractHttpMessage.hpp"

#include "errors/NoSuchHeaderException.hpp"

namespace Lattice::Http {
    AbstractHttpMessage::AbstractHttpMessage(std::vector<Header> headers,
                                             std::string body) : _headers(
            std::move(headers)),
        _body(std::move(body)) {
    }

    AbstractHttpMessage::AbstractHttpMessage(std::vector<Header> headers,
                                             const json &body) : _headers(
            std::move(headers)),
        _body(body.dump()) {
        this->addHeader("Content-Type", "application/json");
    }

    AbstractHttpMessage::~AbstractHttpMessage() = default;

    std::vector<Header> AbstractHttpMessage::getHeaders() const {
        return this->_headers;
    }

    void AbstractHttpMessage::addHeader(const std::string &name,
                                        const std::string &value) {
        this->_headers.emplace_back(name, value);
    }

    void AbstractHttpMessage::addHeader(const Header &header) {
        this->_headers.push_back(header);
    }

    void AbstractHttpMessage::clearHeaders() {
        this->_headers.clear();
    }

    void AbstractHttpMessage::removeHeader(const std::string &name) {
        this->_headers.erase(std::remove_if(this->_headers.begin(), this->_headers.end(),
                                            [&name](const Header &header) {
                                                return header.getName() == name;
                                            }), this->_headers.end());
    }

    bool AbstractHttpMessage::hasHeader(const std::string &name) const {
        return std::any_of(this->_headers.begin(), this->_headers.end(),
                           [&name](const Header &header) {
                               return header.getName() == name;
                           });
    }


    std::string AbstractHttpMessage::getHeader(const std::string &name) const {
        for (const auto &header: this->_headers) {
            if (header.getName() == name) {
                return header.getValue();
            }
        }
        throw NoSuchHeaderException(name);
    }

    std::string AbstractHttpMessage::getHeaderOrDefault(const std::string &name,
                                                        const std::string &defaultV)
    const {
        for (const auto &header: this->_headers) {
            if (header.getName() == name) {
                return header.getValue();
            }
        }
        return defaultV;
    }

    std::string AbstractHttpMessage::getBody() const {
        return this->_body;
    }

    nlohmann::json AbstractHttpMessage::getJsonBody() const {
        try {
            return json::parse(this->_body);
        } catch ([[maybe_unused]] const json::parse_error &e) {
            return {};
        }
    }

    void AbstractHttpMessage::setBody(std::string body) {
        this->_body = std::move(body);
    }

    void AbstractHttpMessage::setBody(const json &body) {
        this->_body = body.dump();
    }

    std::string AbstractHttpMessage::getContent() const {
        return this->toString();
    }

    void AbstractHttpMessage::setContent(const std::string content) {
        this->fromString(content);
    }
}
