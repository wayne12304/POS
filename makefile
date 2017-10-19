INC_DIR = include

all: hw3


hw3: mainTerm.o atom.o term.o number.o variable.o struct.o

ifeq (${OS}, Windows_NT)
	g++ -o hw3 mainTerm.o atom.o term.o number.o variable.o struct.o -lgtest
else
	g++ -o hw3 mainTerm.o atom.o term.o number.o variable.o struct.o -lgtest -lpthread
endif


mainTerm.o: mainTerm.cpp utStruct.h utTerm.h
	g++ -std=gnu++0x -c mainTerm.cpp
	
atom.o: atom.h atom.cpp
	g++ -std=gnu++0x -c atom.cpp
	
term.o: term.h term.cpp
	g++ -std=gnu++0x -c term.cpp
	
number.o: number.h number.cpp
	g++ -std=gnu++0x -c number.cpp
	
variable.o: variable.h variable.cpp
	g++ -std=gnu++0x -c variable.cpp
	
struct.o: struct.h struct.cpp
	g++ -std=gnu++0x -c struct.cpp


clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw3
endif
