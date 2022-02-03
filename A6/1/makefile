CC := g++ -std=c++11

all: a.out

a.out: main.o JsonBuilder.o object.o error.o 
	$(CC) main.o JsonBuilder.o object.o error.o -o 1.out

main.o: JsonBuilder.hpp main.cpp
	$(CC) -c main.cpp -o main.o

JsonBuilder.o: error.hpp object.hpp JsonBuilder.hpp JsonBuilder.cpp
	$(CC) -c JsonBuilder.cpp -o JsonBuilder.o

error.o: error.cpp error.hpp
	$(CC) -c error.cpp -o error.o

object.o: error.hpp object.cpp object.hpp 
	$(CC) -c object.cpp -o object.o

.PHONY: clean

clean:
	rm -r *.oz