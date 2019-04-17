CFLAGS=-std=c++11

main.out: main.o bst.o TTTree.o
	g++ $(CFLAGS) -o main.out main.o bst.o TTTree.o

main.o: bst.h TTTree.h main.cpp
	g++ $(CFLAGS) -c -o main.o main.cpp

bst.o: bst.h bst.cpp
	g++ $(CFLAGS) -c -o  bst.o bst.cpp

TTTree.o: TTTree.h TTTree.cpp
	g++ $(CFLAGS) -c -o TTTree.o TTTree.cpp

clean:
	rm -f *.o *.x *~