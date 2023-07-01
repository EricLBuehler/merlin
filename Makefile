debug:
	g++ src/main.cpp -o merlin -Wall -Wpedantic -std=c++20 -DDEBUG
release:
	g++ src/main.cpp -o merlin -Wall -Wpedantic -std=c++20
clean:
	rm merlin