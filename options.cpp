#include <cryptofuzz/options.h>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <iostream>
#include <stdlib.h>
#include <cryptofuzz/repository.h>

namespace cryptofuzz {

Options::Options(const int argc, char** argv) {
    for (int i = 0; i < argc; i++) {
        arguments.push_back( std::string(argv[i]) );
    }

    for (size_t i = 1; i < arguments.size(); i++) {
        const auto arg = arguments[i];
        std::vector<std::string> parts;
        boost::split(parts, arg, boost::is_any_of("="));

        if ( arg == "--debug" ) {
            debug = true;
        } else if ( !parts.empty() && parts[0] == "--operations" ) {
            if ( parts.size() != 2 ) {
                std::cout << "Expected argument after --operations=" << std::endl;
                exit(1);
            }

            std::vector<std::string> operationStrings;
            boost::split(operationStrings, parts[1], boost::is_any_of(","));

            std::vector<uint64_t> operationIDs;

            for (const auto& curOpStr : operationStrings) {
                bool found = false;
                for (size_t i = 0; i < (sizeof(repository::OperationLUT) / sizeof(repository::OperationLUT[0])); i++) {
                    if ( boost::iequals(curOpStr, std::string(repository::OperationLUT[i].name)) ) {
                        operationIDs.push_back(repository::OperationLUT[i].id);
                        found = true;
                        break;
                    }
                }

                if ( found == false ) {
                    std::cout << "Undefined operation: " << curOpStr << std::endl;
                    exit(1);
                }
            }

            this->operations = operationIDs;
        } else if ( !parts.empty() && parts[0] == "--ciphers" ) {
            if ( parts.size() != 2 ) {
                std::cout << "Expected argument after --ciphers=" << std::endl;
                exit(1);
            }

            std::vector<std::string> cipherStrings;
            boost::split(cipherStrings, parts[1], boost::is_any_of(","));

            std::vector<uint64_t> cipherIDs;

            for (const auto& curOpStr : cipherStrings) {
                bool found = false;
                for (size_t i = 0; i < (sizeof(repository::CipherLUT) / sizeof(repository::CipherLUT[0])); i++) {
                    if ( boost::iequals(curOpStr, std::string(repository::CipherLUT[i].name)) ) {
                        cipherIDs.push_back(repository::CipherLUT[i].id);
                        found = true;
                        break;
                    }
                }

                if ( found == false ) {
                    std::cout << "Undefined cipher: " << curOpStr << std::endl;
                    exit(1);
                }
            }

            this->ciphers = cipherIDs;
        } else if ( !parts.empty() && parts[0] == "--curves" ) {
            if ( parts.size() != 2 ) {
                std::cout << "Expected argument after --curves=" << std::endl;
                exit(1);
            }

            std::vector<std::string> curveStrings;
            boost::split(curveStrings, parts[1], boost::is_any_of(","));

            std::vector<uint64_t> curveIDs;

            for (const auto& curOpStr : curveStrings) {
                bool found = false;
                for (size_t i = 0; i < (sizeof(repository::ECC_CurveLUT) / sizeof(repository::ECC_CurveLUT[0])); i++) {
                    if ( boost::iequals(curOpStr, std::string(repository::ECC_CurveLUT[i].name)) ) {
                        curveIDs.push_back(repository::ECC_CurveLUT[i].id);
                        found = true;
                        break;
                    }
                }

                if ( found == false ) {
                    std::cout << "Undefined curve: " << curOpStr << std::endl;
                    exit(1);
                }
            }

            this->curves = curveIDs;
        } else if ( !parts.empty() && parts[0] == "--force-module" ) {
            if ( parts.size() != 2 ) {
                std::cout << "Expected argument after --force-module=" << std::endl;
                exit(1);
            }

            const auto& moduleStr = parts[1];

            bool found = false;
            uint64_t forceModule;
            for (size_t i = 0; i < (sizeof(repository::ModuleLUT) / sizeof(repository::ModuleLUT[0])); i++) {
                if ( boost::iequals(moduleStr, std::string(repository::ModuleLUT[i].name)) ) {
                    forceModule = repository::ModuleLUT[i].id;
                    found = true;
                    break;
                }
            }

            if ( found == false ) {
                std::cout << "Undefined module: " << moduleStr << std::endl;
                exit(1);
            }

            this->forceModule = forceModule;
        } else if ( !parts.empty() && parts[0] == "--disable-modules" ) {
            if ( parts.size() != 2 ) {
                std::cout << "Expected argument after --disable-modules=" << std::endl;
                exit(1);
            }

            std::vector<std::string> moduleStrings;
            boost::split(moduleStrings, parts[1], boost::is_any_of(","));

            std::vector<uint64_t> moduleIDs;

            for (const auto& curModStr : moduleStrings) {
                bool found = false;
                for (size_t i = 0; i < (sizeof(repository::ModuleLUT) / sizeof(repository::ModuleLUT[0])); i++) {
                    if ( boost::iequals(curModStr, std::string(repository::ModuleLUT[i].name)) ) {
                        moduleIDs.push_back(repository::ModuleLUT[i].id);
                        found = true;
                        break;
                    }
                }

                if ( found == false ) {
                    std::cout << "Undefined module: " << curModStr << std::endl;
                    exit(1);
                }
            }

            this->disableModules = moduleIDs;
        } else if ( !parts.empty() && parts[0] == "--min-modules" ) {
            if ( parts.size() != 2 ) {
                std::cout << "Expected argument after --min-modules=" << std::endl;
                exit(1);
            }

            const auto& moduleStr = parts[1];
            const int minModules = stoi(moduleStr);
            if ( minModules < 1 ) {
                std::cout << "min-modules must be >= 1" << std::endl;
                exit(1);
            }

            this->minModules = static_cast<size_t>(minModules);
        } else if ( !parts.empty() && parts[0] == "--disable-tests" ) {
            if ( parts.size() != 1 ) {
                std::cout << "Expected no argument after --disable-tests=" << std::endl;
                exit(1);
            }
            this->disableTests = true;
        }
    }
}

} /* namespace cryptofuzz */
