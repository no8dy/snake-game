all:
	g++ -c setting.cpp snake.cpp item.cpp clock.cpp
	g++ -o game main.cpp setting.o snake.o item.o clock.o -lncurses -pthread
clean:
	rm -rf *.o game
