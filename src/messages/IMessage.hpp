#ifndef ABSTRACTMESSAGE_HPP
#define ABSTRACTMESSAGE_HPP
#include <string>

namespace Lattice {
    class IMessage {
    protected:
        IMessage();

    public:
        virtual ~IMessage();

        [[nodiscard]]
        virtual std::string getContent() const = 0;

        virtual void setContent(std::string content) = 0;
    };
}

#endif //ABSTRACTMESSAGE_HPP
