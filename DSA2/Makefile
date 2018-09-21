spell.out: spellcheck.o hash.o
	g++ -o spell.out -std=c++11 spellcheck.o hash.o
	
spellcheck.o: spellcheck.cpp hash.h
	g++ -std=c++11 -c spellcheck.cpp

hash.o: hash.cpp hash.h
	g++ -std=c++11 -c hash.cpp

debug:
	g++ -g -o spellDebug.exe spellcheck.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
