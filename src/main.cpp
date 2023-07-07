#include <fstream>
#include <iostream>
#include <string>

#include "termcolor/termcolor.hpp"

#define UNIMPLEMENTED                                                            \
    throw std::runtime_error(std::string("Unimplemented code at ") +    \
                             std::string(__FILE__) + std::string(":") + \
                             std::to_string(__LINE__) + std::string("."))
                             
#define UNREACHABLE                                                            \
    throw std::runtime_error(std::string("Unreachable code at ") +    \
                             std::string(__FILE__) + std::string(":") + \
                             std::to_string(__LINE__) + std::string("."))

#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

int main(int argc, char** argv) {
    std::string filedata = "program.me";
    std::ifstream file(filedata);
    std::string data;
    if (file.is_open()) {
        file >> data;
    }

    lexer::Lexer lexer(data);
#ifdef DEBUG
    std::cout << "===== Lexer start =====\n";
#endif
    auto tokens = lexer.generate_tokens();
#ifdef DEBUG
    for (lexer::Token token : tokens) {
        std::cout << token << std::endl;
    }
    std::cout << "===== Lexer finished =====\n\n";
#endif

    parser::Parser parser(tokens);
#ifdef DEBUG
    std::cout << "===== Parser start =====\n";
#endif
    auto ast = parser.block();
#ifdef DEBUG
    std::cout << "===== Parser finished =====\n\n";
#endif
}