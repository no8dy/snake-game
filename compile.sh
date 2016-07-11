g++ -std=gnu++11 -c setting.cpp move.cpp fire.cpp tree.cpp
g++ -std=gnu++11 -o a.exe snake.cpp setting.o move.o fire.o tree.o -lncurses -pthread
#g++ -std=gnu++11 -o a.exe snake.cpp  -lncurses
