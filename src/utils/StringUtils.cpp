#include "StringUtils.hpp"

#include <cctype>
#include <iomanip>
#include <sstream>

namespace Lattice {
    std::string StringUtils::urlEncode(const std::string &str) {
        std::ostringstream escaped;
        escaped.fill('0');
        escaped << std::hex;

        for (const unsigned char c: str) {
            if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
                escaped << c;
            } else if (c == ' ') {
                escaped << '+';
            } else {
                escaped << '%' << std::setw(2) << static_cast<int>(c);
            }
        }

        return escaped.str();
    }

    std::string StringUtils::urlDecode(const std::string &str) {
        std::ostringstream unescaped;

        for (size_t i = 0; i < str.size(); ++i) {
            if (str[i] == '%') {
                unsigned long c = 0;
                try {
                    c = strtoul(str.substr(i + 1, 2).c_str(), nullptr, 16);
                } catch ([[maybe_unused]] const std::invalid_argument &e) {
                    unescaped << str[i];
                    continue;
                }
                unescaped << static_cast<char>(c);
                i += 2;
            } else if (str[i] == '+') {
                unescaped << ' ';
            } else {
                unescaped << str[i];
            }
        }

        return unescaped.str();
    }

    std::string StringUtils::join(const std::vector<std::string> &strings,
                                  const std::string &delimiter) {
        std::string result;
        for (size_t i = 0; i < strings.size(); ++i) {
            result += strings[i];
            if (i != strings.size() - 1) {
                result += delimiter;
            }
        }
        return result;
    }

    std::vector<std::string> StringUtils::split(const std::string &str,
                                                const std::string &delimiter) {
        std::vector<std::string> result;
        size_t start = 0;
        size_t end = str.find(delimiter);
        while (end != std::string::npos) {
            result.push_back(str.substr(start, end - start));
            start = end + delimiter.size();
            end = str.find(delimiter, start);
        }
        result.push_back(str.substr(start, end));
        return result;
    }
} // Lattice
