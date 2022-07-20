.PHONY: all clean
CC = g++
CFLAGS = -std=c++17 -O3 -Wall -Wextra -pedantic

all: main.o encode.o decode.o util.o
	$(CC) $^ -o main $(CFLAGS) 

main.o: main.cpp 
	$(CC) -c $< $(CFLAGS)

encode.o: Encode.cpp Encode.h
	$(CC) -c $< $(CFLAGS)

decode.o: Decode.cpp Decode.h
	$(CC) -c $< $(CFLAGS)

util.o: util.cpp util.h
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f main *.o


