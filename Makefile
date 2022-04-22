.PHONY: all clean
CC = g++
CFLAGS = -std=c++17 -O2 -Wall -Wextra -pedantic

all: main
	$(CC) main.o -o main $(CFLAGS)

main: main.cpp
	$(CC) -c main.cpp $(CFLAGS)

clean:
	rm -f main *.o


