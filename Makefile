CXX = g++
CXXFLAGS = -Wall

compile: proj2

proj2: Driver.o TestBinarySearchTree.o Word.o Indexer.o
	$(CXX) $(CXXFLAGS) Driver.o TestBinarySearchTree.o Word.o Indexer.o -o proj2

Driver.o: Driver.cpp
	$(CXX) $(CXXFLAGS) -c Driver.cpp	

TestBinarySearchTree.o: TestBinarySearchTree.cpp
	$(CXX) $(CXXFLAGS) -c TestBinarySearchTree.cpp

Word.o: Word.h Word.cpp
	$(CXX) $(CXXFLAGS) -c Word.cpp

Indexer.o: Indexer.h Indexer.cpp
	$(CXX) $(CXXFLAGS) -c Indexer.cpp



clean:
	rm proj2 *o *~

run:
	./proj2 $(FILTER) $(DATA)

run1:
	./proj2 gsl.txt input1.txt

run2:
	./proj2 gsl.txt input2.txt

val1:
	valgrind ./proj2 gsl.txt input1.txt

val2:
	valgrind ./proj2 gsl.txt input2.txt


