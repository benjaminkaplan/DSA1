checkers.out: checkers.o board.o
	g++ -o checkers.out checkers.o board.o -std=c++11

checkers.o: checkers.cpp board.h
	g++ -c checkers.cpp -std=c++11


board.o: board.h board.cpp
	g++ -c board.cpp -std=c++11
