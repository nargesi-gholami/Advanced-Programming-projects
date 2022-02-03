CC := g++ -std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: a.out

a.out: main.o enemy.o Tower.o Player.o Game.o rsdl.o bullet.o
	$(CC) main.o enemy.o Tower.o Player.o Game.o rsdl.o bullet.o $(CCFLAGS) -o FieldRunners.out

main.o:  Game.hpp main.cpp
	$(CC) -c main.cpp -o main.o

enemy.o: rsdl.hpp enemy.hpp enemy.cpp
	$(CC) -c enemy.cpp -o enemy.o

Tower.o: rsdl.hpp Tower.hpp enemy.hpp bullet.hpp tower.cpp
	$(CC) -c tower.cpp -o Tower.o

Player.o: rsdl.hpp Player.hpp Player.cpp
	$(CC) -c Player.cpp -o Player.o

bullet.o: rsdl.hpp bullet.hpp enemy.hpp bullet.cpp
	$(CC) -c bullet.cpp -o bullet.o

Game.o: rsdl.hpp Tower.hpp enemy.hpp Player.hpp bullet.hpp Game.cpp
	$(CC) -c Game.cpp -o Game.o

rsdl.o: rsdl.hpp rsdl.cpp
	$(CC) -c rsdl.cpp -o rsdl.o

.PHONY: clean

clean:
	rm -r *.oz