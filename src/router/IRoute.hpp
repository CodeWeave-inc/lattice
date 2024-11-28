#ifndef IROUTE_HPP
#define IROUTE_HPP
#include "../messages/IMessage.hpp"

namespace Lattice {
    class IRoute {
    protected:
        IRoute();

    public:
        virtual ~IRoute();

        virtual bool canAccept(IMessage *message) const = 0;

        virtual IMessage *handle(IMessage *message) const = 0;
    };
}

#endif //IROUTE_HPP
