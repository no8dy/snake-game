all:
	g++ -std=gnu++11 -c setting.cpp move.cpp fire.cpp tree.cpp
	g++ -std=gnu++11 -o game snake.cpp setting.o move.o fire.o tree.o -lncurses -pthread

clean:
	rm -rf *.o game
