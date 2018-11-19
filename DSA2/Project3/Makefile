doDijkstra.out: doDijkstra.o heap.o hash.o graph.o
	g++ -std=c++11 -o doDijkstra.out doDijkstra.o graph.o heap.o hash.o

doDijkstra.o: doDijkstra.cpp
	g++ -std=c++11 -c doDijkstra.cpp

graph.o: graph.cpp graph.h
	g++ -std=c++11 -c graph.cpp

heap.o: heap.cpp heap.h
	g++ -std=c++11 -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -std=c++11 -c hash.cpp

debug:
	g++ -g -o useHeapDebug.exe useHeap.cpp heap.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
