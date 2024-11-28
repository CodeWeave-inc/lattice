#ifndef REQUEST_HPP
#define REQUEST_HPP
#include <unordered_map>

#include "AbstractHttpMessage.hpp"


namespace Lattice::Http {
    using Query = std::pair<std::string, std::string>;
    using QueryMap = std::unordered_map<std::string, std::string>;

    enum class Method {
        GET,
        POST,
        PUT,
        DELETE,
        PATCH,
        OPTIONS,
        HEAD,
        CONNECT,
        TRACE
    };

    std::string methodToString(Method method);

    Method stringToMethod(const std::string &string);

    class Request final : public AbstractHttpMessage {
    protected:
        Method _method;
        std::string _uri;
        QueryMap _queries;

    public:
        explicit Request(Method method, const std::vector<Header> &headers = {},
                         const std::string &body = "");

        explicit Request(Method method, const std::vector<Header> &headers = {},
                         const json &body = {});


        ~Request() override;

        // Queries
        [[nodiscard]] QueryMap getQueries() const;

        [[nodiscard]] Query getQuery(const std::string &name) const;

        [[nodiscard]] bool hasQuery(const std::string &name) const;

        [[nodiscard]] Query getQueryOrDefault(const std::string &name,
                                              const std::string &defaultV) const;

        void addQuery(const std::string &name, const std::string &value);

        void removeQuery(const std::string &name);

        void clearQueries();

        // Method
        [[nodiscard]] Method getMethod() const;

        void setMethod(Method method);

        // URI
        [[nodiscard]] std::string getUri() const;

        [[nodiscard]] std::string getUriWithQueries() const;

        // Serialization and deserialization
        [[nodiscard]] std::string toString() const override;

        void fromString(const std::string &string) override;
    };
}

#endif //REQUEST_HPP
