INC_DIR = include

all: hw5


hw5: mainParser.o atom.o list.o

ifeq (${OS}, Windows_NT)
	g++ -o hw5 mainParser.o atom.o list.o -lgtest
else
	g++ -o hw5 mainParser.o atom.o list.o -lgtest -lpthread
endif


mainParser.o: mainParser.cpp utParser.h 
	g++ -std=gnu++0x -c mainParser.cpp
	
atom.o: atom.h atom.cpp variable.h struct.h scanner.h parser.h
	g++ -std=gnu++0x -c atom.cpp
	
list.o: list.h list.cpp
	g++ -std=gnu++0x -c list.cpp
	

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw5
endif
