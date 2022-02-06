prog: main.o executive.o game.o
	g++ -std=c++17 -g -Wall main.o executive.o game.o -o prog

main.o: main.cpp executive.h 
	g++ -std=c++17 -g -Wall -c main.cpp

executive.o: executive.h executive.cpp game.h player.h
	g++ -std=c++17 -g -Wall -c executive.cpp

game.o: game.h game.cpp
	g++ -std=c++17 -g -Wall -c game.cpp

player.o: player.h player.cpp
	g++ -std=c++17 -g -Wall -c player.cpp

clean:
	rm *.o prog
