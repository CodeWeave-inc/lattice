#ifndef HEADER_HPP
#define HEADER_HPP
#include <string>

namespace Lattice::Http {
    class Header final {
    protected:
        std::string _name;
        std::string _value;

    public:
        explicit Header(std::string name, std::string value = "");

        ~Header();

        [[nodiscard]] std::string getName() const;

        [[nodiscard]] std::string getValue() const;

        void setName(std::string name);

        void setValue(std::string value);

        void appendValue(std::string value);

        void clearValue();
    };
}

#endif //HEADER_HPP
