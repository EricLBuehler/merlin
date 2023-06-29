debug:
	g++ src/main.cpp -o merlin -Wall -Wpedantic -std=c++23 -DDEBUG
release:
	g++ src/main.cpp -o merlin -Wall -Wpedantic -std=c++23
clean:
	rm merlin