CC := g++ -std=c++11

all: a.out

a.out: main.o hotel_consumer.o reception.o hotel.o filter.o Room.o
	$(CC) main.o reception.o hotel.o hotel_consumer.o filter.o Room.o -o utrip.out

main.o: reception.hpp main.cpp
	$(CC) -c main.cpp

reception.o: filter.hpp hotel_consumer.hpp hotel.hpp reception.hpp Room.hpp reception.cpp
	$(CC) -c reception.cpp reception.hpp

hotel.o: Room.hpp hotel_consumer.hpp hotel.cpp hotel.hpp
	$(CC) -c hotel.cpp hotel.hpp  

hotel_consumer.o: Room.hpp hotel_consumer.hpp hotel_consumer.cpp
	$(CC) -c hotel_consumer.cpp hotel_consumer.hpp

filter.o: hotel.hpp filter.cpp filter.hpp
	$(CC) -c filter.cpp filter.hpp

Room.o: Room.hpp Room.cpp
	$(CC) -c Room.hpp Room.cpp 

.PHONY: clean

clean:
	rm -r *.oz