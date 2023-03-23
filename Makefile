tic-tac-toe: main.cpp game.cpp cell.cpp game.h cell.h
	g++ main.cpp game.cpp cell.cpp -o tic-tac-toe `wx-config --libs --cppflags` -g

.PHONY: clean
clean:
	rm -f tic-tac-toe
