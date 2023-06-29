#include <iostream>
#include <fstream>
#include <string>

#include "termcolor/termcolor.hpp"

#include "lexer/lexer.hpp"


int main(int argc, char** argv) {
    std::string filedata = "program.me";
    std::ifstream file(filedata);
    std::string data;
    if (file.is_open()) {
        file >> data;
    }
    
    lexer::Lexer lexer(data);
    std::vector<lexer::Token> tokens = lexer.generate_tokens();
    #ifdef DEBUG
    for (lexer::Token token: tokens) {
        std::cout<<token<<std::endl;
    }
    #endif
}