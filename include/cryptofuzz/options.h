#pragma once

#include <string>
#include <vector>
#include <optional>
#include <cstdint>

namespace cryptofuzz {

class Options {
    private:
        std::vector<std::string> arguments;
    public:
        Options(const int argc, char** argv);

        std::optional<std::vector<uint64_t>> operations = std::nullopt;
        std::optional<std::vector<uint64_t>> ciphers = std::nullopt;
        std::optional<std::vector<uint64_t>> curves = std::nullopt;
        std::optional<uint64_t> forceModule = std::nullopt;
        std::optional<std::vector<uint64_t>> disableModules = std::nullopt;
        size_t minModules = 1;
        bool debug = false;
        bool disableTests = false;
};

} /* namespace cryptofuzz */
