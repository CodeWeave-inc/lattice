#ifndef AROUTER_HPP
#define AROUTER_HPP
#include <unordered_map>

#include "IRoute.hpp"
#include "../messages/IMessage.hpp"

namespace Lattice {
    class Router final {
    protected:
        std::unordered_map<int, IRoute *> _routes;
        IRoute *_notFoundRoute;

    public:
        Router();

        ~Router();

        IMessage *route(IMessage *message) const;

        int addRoute(IRoute *route);

        void removeRoute(int id);

        void setNotFoundRoute(IRoute *route);

        [[nodiscard]] const IRoute *getRoute(int id) const;
    };
}

#endif //AROUTER_HPP
