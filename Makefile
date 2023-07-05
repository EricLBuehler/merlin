debug:
	g++ src/main.cpp -o merlin -Wall -Wpedantic -std=c++20 -DDEBUG
release:
	g++ src/main.cpp -o merlin -Wall -Wpedantic -std=c++20
clean:
	rm merlin
fmt:
	clang-format -style="{BasedOnStyle: Google, IndentWidth: 4}" -i src/main.cpp
	clang-format -style="{BasedOnStyle: Google, IndentWidth: 4}" -i src/parser/*.cpp src/parser/*.hpp
	clang-format -style="{BasedOnStyle: Google, IndentWidth: 4}" -i src/lexer/*.cpp src/lexer/*.hpp
	clang-format -style="{BasedOnStyle: Google, IndentWidth: 4}" -i src/termcolor/*.hpp