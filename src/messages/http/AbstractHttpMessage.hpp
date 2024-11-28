#ifndef ABSTRACTHTTPMESSAGE_HPP
#define ABSTRACTHTTPMESSAGE_HPP
#include <vector>
#include <nlohmann/json.hpp>

#include "Header.hpp"
#include "../IMessage.hpp"

namespace Lattice::Http {
    class AbstractHttpMessage : public IMessage {
    protected:
        std::vector<Header> _headers;
        std::string _body;
        using json = nlohmann::json;

        AbstractHttpMessage(std::vector<Header> headers, std::string body);

        AbstractHttpMessage(std::vector<Header> headers, const json &body);

    public:
        ~AbstractHttpMessage() override;

        // Headers
        [[nodiscard]] std::vector<Header> getHeaders() const;

        void addHeader(const Header &header);

        void addHeader(const std::string &name, const std::string &value);

        void removeHeader(const std::string &name);

        void clearHeaders();

        [[nodiscard]] std::string getHeader(const std::string &name) const;

        [[nodiscard]] std::string getHeaderOrDefault(const std::string &name,
                                                     const std::string &defaultV) const;

        [[nodiscard]] bool hasHeader(const std::string &name) const;

        // Body
        [[nodiscard]] std::string getBody() const;

        [[nodiscard]] json getJsonBody() const;

        void setBody(std::string body);

        void setBody(const json &body);

        // Serialization and deserialization
        [[nodiscard]] virtual std::string toString() const = 0;

        virtual void fromString(const std::string &string) = 0;

        void setContent(std::string content) override;

        [[nodiscard]] std::string getContent() const override;
    };
}

#endif //ABSTRACTHTTPMESSAGE_HPP
