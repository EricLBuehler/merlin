#include <iostream>
#include <sstream>

#include "termcolor/termcolor.hpp"

int main(int argc, char** argv) {
    std::cout << termcolor::green << "Welcome to Merlin!\n" << termcolor::reset;
}