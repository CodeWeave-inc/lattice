from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMakeToolchain, CMakeDeps


class ConanApplication(ConanFile):
    package_type = "application"
    settings = "os", "compiler", "build_type", "arch"

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def requirements(self):
        self.requires("gtest/1.15.0")
        self.requires("spdlog/1.15.0")
        self.requires("asio/1.32.0")
        self.requires("cpptrace/0.7.3")
        self.requires("nlohmann_json/3.11.3")
