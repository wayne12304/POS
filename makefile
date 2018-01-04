all: hw8 shell

hw8: mainExpression.o atom.o struct.o list.o

ifeq (${OS}, Windows_NT)
	g++ -o hw8 mainExpression.o atom.o list.o struct.o -lgtest
else
	g++ -o hw8 mainExpression.o atom.o list.o struct.o -lgtest -lpthread
endif

shell: main.o atom.o struct.o list.o

ifeq (${OS}, Windows_NT)
	g++ -o shell main.o atom.o list.o struct.o -lgtest
else
	g++ -o shell main.o atom.o list.o struct.o -lgtest -lpthread
endif

atom.o: atom.cpp atom.h variable.h
	g++ -std=c++11 -c atom.cpp
list.o:list.cpp list.h
		g++ -std=c++11 -c list.cpp
struct.o:struct.cpp struct.h
		g++ -std=c++11 -c struct.cpp
#exp: mainExp.o
#	g++ -o exp mainExp.o -lgtest -lpthread
#mainExp.o: mainExp.cpp exp.h global.h
#	g++ -std=c++11 -c mainExp.cpp

mainExpression.o: mainExpression.cpp expression.h exception.h
	g++ -std=c++11 -c mainExpression.cpp
	
main.o: main.cpp 
	g++ -std=c++11 -c main.cpp

#utTerm: mainTerm.o term.o struct.o var.o list.o
#	g++ -o utTerm mainTerm.o term.o var.o struct.o list.o -lgtest -lpthread
#mainTerm.o: mainTerm.cpp utTerm.h term.h var.h utStruct.h struct.h list.h utList.h
#	g++ -std=c++11 -c mainTerm.cpp
#term.o: term.h term.cpp
#	g++ -std=c++11 -c term.cpp
#struct.o: struct.h struct.cpp
#	g++ -std=c++11 -c struct.cpp
#var.o: var.h var.cpp
#g++ -std=c++11 -c var.cpp
#list.o: list.h list.cpp term.h var.h
#	g++ -std=c++11 -c list.cpp
clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw8 shell
endif

stat:
	wc *.h *.cpp
