#include "Request.hpp"

#include <spdlog/spdlog.h>

#include "../../utils/StringUtils.hpp"
#include "errors/HttpVersionNotSupported.hpp"
#include "errors/MethodNotAllowed.hpp"
#include "errors/NoSuchQueryException.hpp"

namespace Lattice::Http {
    Request::Request(const Method method, const std::vector<Header> &headers,
                     const std::string &body)
        : AbstractHttpMessage(headers, body), _method(method) {
    }

    Request::Request(const Method method, const std::vector<Header> &headers,
                     const json &body)
        : AbstractHttpMessage(headers, body), _method(method) {
    }

    Request::~Request() = default;

    void Request::addQuery(const std::string &name, const std::string &value) {
        this->_queries[name] = value;
    }

    void Request::removeQuery(const std::string &name) {
        this->_queries.erase(name);
    }

    void Request::clearQueries() {
        this->_queries.clear();
    }

    QueryMap Request::getQueries() const {
        return this->_queries;
    }

    Query Request::getQuery(const std::string &name) const {
        if (!this->hasQuery(name)) {
            throw NoSuchQueryException(name);
        }
        return {name, this->_queries.at(name)};
    }

    bool Request::hasQuery(const std::string &name) const {
        return this->_queries.find(name) != this->_queries.end();
    }

    Query Request::getQueryOrDefault(const std::string &name,
                                     const std::string &defaultV) const {
        if (this->hasQuery(name)) {
            return this->getQuery(name);
        }
        return {name, defaultV};
    }

    Method Request::getMethod() const {
        return this->_method;
    }

    void Request::setMethod(const Method method) {
        this->_method = method;
    }

    std::string methodToString(const Method method) {
        switch (method) {
            case Method::GET:
                return "GET";
            case Method::POST:
                return "POST";
            case Method::PUT:
                return "PUT";
            case Method::DELETE:
                return "DELETE";
            case Method::PATCH:
                return "PATCH";
            case Method::OPTIONS:
                return "OPTIONS";
            case Method::HEAD:
                return "HEAD";
            case Method::CONNECT:
                return "CONNECT";
            case Method::TRACE:
                return "TRACE";
        }
        return "";
    }

    Method stringToMethod(const std::string &string) {
        if (string == "GET") {
            return Method::GET;
        }
        if (string == "POST") {
            return Method::POST;
        }
        if (string == "PUT") {
            return Method::PUT;
        }
        if (string == "DELETE") {
            return Method::DELETE;
        }
        if (string == "PATCH") {
            return Method::PATCH;
        }
        if (string == "OPTIONS") {
            return Method::OPTIONS;
        }
        if (string == "HEAD") {
            return Method::HEAD;
        }
        if (string == "CONNECT") {
            return Method::CONNECT;
        }
        if (string == "TRACE") {
            return Method::TRACE;
        }
        spdlog::error("Unknown method: {}", string);
        throw MethodNotAllowed();
    }

    std::string Request::getUri() const {
        return this->_uri;
    }

    std::string Request::getUriWithQueries() const {
        std::string uri = this->_uri;
        if (!this->_queries.empty()) {
            uri += "?";
            for (const auto &[name, value]: this->_queries) {
                uri += StringUtils::urlEncode(name) + "=" + StringUtils::urlEncode(value)
                        + "&";
            }
            uri.pop_back();
        }
        return uri;
    }

    std::string Request::toString() const {
        const std::string requestLine = methodToString(this->_method) + " " + this->
                                        getUriWithQueries()
                                        + " HTTP/" + HTTP_VERSION + "\r\n";
        std::vector<std::string> headersLines;
        for (const auto &header: this->_headers) {
            headersLines.push_back(header.getName() + ": "
                                   + header.getValue() + "\r\n");
        }
        const std::string headers = StringUtils::join(headersLines, "");

        return requestLine + headers + "\r\n" + this->_body;
    }

    static bool compatibleWithHttpVersion(const std::string &httpVersion) {
        const int usMajor = std::stoi(std::string(1, HTTP_VERSION[0]));
        const int usMinor = std::stoi(std::string(1, HTTP_VERSION[2]));

        const int themMajor = std::stoi(std::string(1, httpVersion[0]));
        const int themMinor = std::stoi(std::string(1, httpVersion[2]));

        if (usMajor != themMajor) {
            return false;
        }
        if (usMinor < themMinor) {
            return false;
        }
        return true;
    }

    void Request::fromString(const std::string &string) {
        const std::size_t requestLineEnd = string.find("\r\n");
        const std::string requestLine = string.substr(0, requestLineEnd);
        const std::size_t headers = string.find("\r\n\r\n");
        const std::string headersString = string.substr(
            requestLineEnd + 2, headers - requestLineEnd - 2);
        const std::string body = string.substr(headers + 4);

        const std::vector<std::string> requestLineParts = StringUtils::split(
            requestLine, " ");
        const Method method = stringToMethod(requestLineParts[0]);
        std::string uri = requestLineParts[1];
        const std::string &httpVersion = requestLineParts[2].substr(5);

        if (!compatibleWithHttpVersion(httpVersion)) {
            throw HttpVersionNotSupported();
        }

        std::vector<Header> headersVector;
        for (const auto &headerLine: StringUtils::split(headersString, "\r\n")) {
            const std::vector<std::string> headerParts = StringUtils::split(headerLine,
                ": ");
            headersVector.emplace_back(headerParts[0],
                                       headerParts[1]);
        }

        std::vector<Query> queriesVector;
        const std::size_t queryStart = uri.find('?');
        if (queryStart != std::string::npos) {
            const std::string queriesString = uri.substr(queryStart + 1);
            for (const auto &query: StringUtils::split(queriesString, "&")) {
                const std::vector<std::string> queryParts =
                        StringUtils::split(query, "=");
                queriesVector.emplace_back(StringUtils::urlDecode(queryParts[0]),
                                           StringUtils::urlDecode(queryParts[1]));
            }
            uri = uri.substr(0, queryStart);
        }

        this->_method = method;
        this->_uri = uri;
        this->_headers = headersVector;
        this->_queries = QueryMap(queriesVector.begin(), queriesVector.end());
        for (const auto &[name, value]: queriesVector) {
            this->_queries[StringUtils::urlDecode(name)] = StringUtils::urlDecode(value);
        }
        this->_body = body;
    }
}
