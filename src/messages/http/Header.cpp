#include "Header.hpp"

namespace Lattice::Http {
    Header::Header(std::string name, std::string value) : _name(std::move(name)),
                                                          _value(std::move(value)) {
    }

    Header::~Header() = default;

    std::string Header::getName() const {
        return _name;
    }

    std::string Header::getValue() const {
        return _value;
    }

    void Header::setName(std::string name) {
        this->_name = std::move(name);
    }

    void Header::setValue(std::string value) {
        this->_value = std::move(value);
    }

    void Header::appendValue(std::string value) {
        this->_value += ", " + std::move(value);
    }

    void Header::clearValue() {
        _value.clear();
    }
}
