INC_DIR = include

all: hw4


hw4: mainList.o atom.o list.o

ifeq (${OS}, Windows_NT)
	g++ -o hw4 mainList.o atom.o list.o -lgtest
else
	g++ -o hw4 mainList.o atom.o list.o -lgtest -lpthread
endif


mainList.o: mainList.cpp utList.h
	g++ -std=gnu++0x -c mainList.cpp
	
atom.o: atom.h atom.cpp variable.h struct.h
	g++ -std=gnu++0x -c atom.cpp
	
list.o: list.h list.cpp
	g++ -std=gnu++0x -c list.cpp
	

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw4
endif
