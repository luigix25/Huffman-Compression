.PHONY: all clean
CC = g++
CFLAGS = -std=c++17 -O2 -Wall -Wextra -pedantic

all: main.o encode.o decode.o
	$(CC) main.o encode.o decode.o -o main $(CFLAGS)

main.o: main.cpp
	$(CC) -c main.cpp $(CFLAGS)

encode.o: Encode.cpp
	$(CC) -c Encode.cpp $(CFLAGS)

decode.o: Decode.cpp
	$(CC) -c Decode.cpp $(CFLAGS)

clean:
	rm -f main *.o


