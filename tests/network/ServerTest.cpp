#include <gtest/gtest.h>

#include "../../src/messages/http/errors/NotFound.hpp"
#include "../../src/network/http/HttpServer.hpp"
#include "../../src/router/http/HttpRouteBuilder.hpp"

class TestEndpoint final : public Lattice::Http::HttpEndpoint {
public:
    TestEndpoint()
        : HttpEndpoint(Lattice::Http::Method::GET) {
    }

    std::variant<Lattice::Http::Response *, Lattice::Http::AHttpError *> handle(
        Lattice::Http::Request *request) override {
        return new Lattice::Http::Response({}, nlohmann::json{
                                               {"message", "Hello, World!"},
                                               {"path", request->getUri()}
                                           }, 200);
    }
};

class NotFoundEndpoint final : public Lattice::Http::HttpEndpoint {
public:
    NotFoundEndpoint(): HttpEndpoint(Lattice::Http::Method::GET) {
    }

    ~NotFoundEndpoint() override = default;

    std::variant<Lattice::Http::Response *, Lattice::Http::AHttpError *> handle(
        Lattice::Http::Request *request) override {
        throw Lattice::Http::NotFound();
    }
};


TEST(HttpServer, Constructor) {
    Lattice::Router router;
    Lattice::Http::HttpServer server(&router, 8080);

    router.addRoute(Lattice::Http::HttpRouteBuilder("/test")
        .build(new TestEndpoint()));
    router.setNotFoundRoute(Lattice::Http::HttpRouteBuilder("/404")
        .build(new NotFoundEndpoint()));

    server.start();

    while (server.isRunning());
}
