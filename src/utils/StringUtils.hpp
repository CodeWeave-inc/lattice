#ifndef STRINGUTILS_HPP
#define STRINGUTILS_HPP
#include <string>
#include <vector>

namespace Lattice {
    class StringUtils final {
    public:
        static std::string urlEncode(const std::string &str);

        static std::string urlDecode(const std::string &str);

        static std::string join(const std::vector<std::string> &strings,
                                const std::string &delimiter);

        static std::vector<std::string> split(const std::string &str,
                                              const std::string &delimiter);
    };
}

#endif //STRINGUTILS_HPP
