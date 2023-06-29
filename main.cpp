#include <iostream>
#include "termcolor/termcolor.hpp"

int main(int argc, char** argv) {
    std::u8string str = u8"This is a u8 string\n";
    std::cout << termcolor::green << "Welcome to Merlin!\n" << termcolor::reset;
    std::cout << reinterpret_cast<const char*>(str.c_str());
}