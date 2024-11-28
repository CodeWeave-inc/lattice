#include "Response.hpp"
#include "../../utils/StringUtils.hpp"
#include <string>

namespace Lattice::Http {
    Response::Response(const std::vector<Header> &headers, const std::string &body,
                       const unsigned short statusCode): AbstractHttpMessage(
                                                             headers, body),
                                                         _statusCode(statusCode) {
        if (statusCode < 100 || statusCode > 599) {
            throw std::invalid_argument(
                "Invalid status code: " + std::to_string(statusCode));
        }
    }

    Response::Response(const std::vector<Header> &headers, const json &body,
                       const unsigned short statusCode): AbstractHttpMessage(
                                                             headers, body),
                                                         _statusCode(statusCode) {
        if (statusCode < 100 || statusCode > 599) {
            throw std::invalid_argument(
                "Invalid status code: " + std::to_string(statusCode));
        }
    }

    Response::~Response() = default;

    void Response::setStatusCode(unsigned short statusCode) {
        if (statusCode < 100 || statusCode > 599) {
            throw std::invalid_argument(
                "Invalid status code: " + std::to_string(statusCode));
        }
        this->_statusCode = statusCode;
    }

    unsigned short Response::getStatusCode() const {
        return this->_statusCode;
    }

    std::string Response::reasonFromStatus(unsigned short statusCode) {
        if (statusCode == 100) {
            return "Continue";
        }
        if (statusCode == 101) {
            return "Switching Protocols";
        }
        if (statusCode == 102) {
            return "Processing";
        }
        if (statusCode == 103) {
            return "Early Hints";
        }
        if (statusCode == 200) {
            return "OK";
        }
        if (statusCode == 201) {
            return "Created";
        }
        if (statusCode == 202) {
            return "Accepted";
        }
        if (statusCode == 203) {
            return "Non-Authoritative Information";
        }
        if (statusCode == 204) {
            return "No Content";
        }
        if (statusCode == 205) {
            return "Reset Content";
        }
        if (statusCode == 206) {
            return "Partial Content";
        }
        if (statusCode == 207) {
            return "Multi-Status";
        }
        if (statusCode == 208) {
            return "Already Reported";
        }
        if (statusCode == 226) {
            return "IM Used";
        }
        if (statusCode == 300) {
            return "Multiple Choices";
        }
        if (statusCode == 301) {
            return "Moved Permanently";
        }
        if (statusCode == 302) {
            return "Found";
        }
        if (statusCode == 303) {
            return "See Other";
        }
        if (statusCode == 304) {
            return "Not Modified";
        }
        if (statusCode == 305) {
            return "Use Proxy";
        }
        if (statusCode == 306) {
            return "Switch Proxy";
        }
        if (statusCode == 307) {
            return "Temporary Redirect";
        }
        if (statusCode == 308) {
            return "Permanent Redirect";
        }
        if (statusCode == 400) {
            return "Bad Request";
        }
        if (statusCode == 401) {
            return "Unauthorized";
        }
        if (statusCode == 402) {
            return "Payment Required";
        }
        if (statusCode == 403) {
            return "Forbidden";
        }
        if (statusCode == 404) {
            return "Not Found";
        }
        if (statusCode == 405) {
            return "Method Not Allowed";
        }
        if (statusCode == 406) {
            return "Not Acceptable";
        }
        if (statusCode == 407) {
            return "Proxy Authentication Required";
        }
        if (statusCode == 408) {
            return "Request Timeout";
        }
        if (statusCode == 409) {
            return "Conflict";
        }
        if (statusCode == 410) {
            return "Gone";
        }
        if (statusCode == 411) {
            return "Length Required";
        }
        if (statusCode == 412) {
            return "Precondition Failed";
        }
        if (statusCode == 413) {
            return "Payload Too Large";
        }
        if (statusCode == 414) {
            return "URI Too Long";
        }
        if (statusCode == 415) {
            return "Unsupported Media Type";
        }
        if (statusCode == 416) {
            return "Range Not Satisfiable";
        }
        if (statusCode == 417) {
            return "Expectation Failed";
        }
        if (statusCode == 418) {
            return "I'm a teapot";
        }
        if (statusCode == 421) {
            return "Misdirected Request";
        }
        if (statusCode == 422) {
            return "Unprocessable Entity";
        }
        if (statusCode == 423) {
            return "Locked";
        }
        if (statusCode == 424) {
            return "Failed Dependency";
        }
        if (statusCode == 425) {
            return "Too Early";
        }
        if (statusCode == 426) {
            return "Upgrade Required";
        }
        if (statusCode == 428) {
            return "Precondition Required";
        }
        if (statusCode == 429) {
            return "Too Many Requests";
        }
        if (statusCode == 431) {
            return "Request Header Fields Too Large";
        }
        if (statusCode == 451) {
            return "Unavailable For Legal Reasons";
        }
        if (statusCode == 500) {
            return "Internal Server Error";
        }
        if (statusCode == 501) {
            return "Not Implemented";
        }
        if (statusCode == 502) {
            return "Bad Gateway";
        }
        if (statusCode == 503) {
            return "Service Unavailable";
        }
        if (statusCode == 504) {
            return "Gateway Timeout";
        }
        if (statusCode == 505) {
            return "HTTP Version Not Supported";
        }
        if (statusCode == 506) {
            return "Variant Also Negotiates";
        }
        if (statusCode == 507) {
            return "Insufficient Storage";
        }
        if (statusCode == 508) {
            return "Loop Detected";
        }
        if (statusCode == 510) {
            return "Not Extended";
        }
        if (statusCode == 511) {
            return "Network Authentication Required";
        }
        return "Unknown";
    }


    std::string Response::toString() const {
        const std::string temp = "";
        const std::string statusLine = temp + "HTTP/" + HTTP_VERSION + " "
                                       + std::to_string(this->_statusCode) + " "
                                       + reasonFromStatus(this->_statusCode) + "\r\n";

        std::vector<std::string> headersLines;
        for (const auto &header: this->_headers) {
            headersLines.push_back(header.getName() + ": "
                                   + header.getValue() + "\r\n");
        }
        const std::string headers = StringUtils::join(headersLines, "");

        return statusLine + headers + "\r\n" + this->_body;
    }

    void Response::fromString(const std::string &string) {
        const std::size_t statusLineEnd = string.find("\r\n");
        const std::string statusLine = string.substr(0, statusLineEnd);
        const std::size_t headers = string.find("\r\n\r\n");
        const std::string headersString = string.substr(
            statusLineEnd + 2, headers - statusLineEnd - 2);
        const std::string body = string.substr(headers + 4);

        int statusCode;
        const std::vector<std::string> statusLineParts = StringUtils::split(
            statusLine, " ");
        try {
            statusCode = std::stoi(statusLineParts[1]);
        } catch ([[maybe_unused]] const std::invalid_argument &e) {
            throw std::invalid_argument("Invalid status code: " + statusLineParts[1]);
        }
        this->_statusCode = statusCode;

        std::vector<Header> headersVector;
        for (const auto &header: StringUtils::split(headersString, "\r\n")) {
            const std::vector<std::string> headerParts = StringUtils::split(header, ": ");
            if (headerParts.size() != 2) {
                throw std::invalid_argument("Invalid header: " + header);
            }
            headersVector.emplace_back(headerParts[0], headerParts[1]);
        }
        this->_headers = headersVector;
        this->_body = body;
    }
}
