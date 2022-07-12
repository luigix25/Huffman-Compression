.PHONY: all clean
CC = g++
CFLAGS = -std=c++17 -O3 -Wall -Wextra -pedantic

all: main.o encode.o decode.o
	$(CC) main.o encode.o decode.o -o main $(CFLAGS)

main.o: main.cpp 
	$(CC) -c main.cpp $(CFLAGS)

encode.o: Encode.cpp Encode.h
	$(CC) -c Encode.cpp $(CFLAGS)

decode.o: Decode.cpp Decode.h
	$(CC) -c Decode.cpp $(CFLAGS)

clean:
	rm -f main *.o


