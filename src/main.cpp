#include <iostream>
#include <sstream>

#include "termcolor/termcolor.hpp"

#include "trc/trc.cpp"

int main(int argc, char** argv) {
    std::u8string str = u8"This is a u8 string\n";
    Trc<std::u8string> data(u8"This is a u8 string\n");

    std::cout << termcolor::green << "Welcome to Merlin!\n" << termcolor::reset;
    std::cout << reinterpret_cast<const char*>(data->c_str());
    
    std::ostringstream out;
    out << std::hex << data.pointer_value() << "\n";
    std::cout << out.str();
}