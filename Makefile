CXX = g++
CXXFLAGS = -Wall

proj2: Driver.o TestBinarySearchTree.o Word.o Indexer.o BinarySearchTree.o
  $(CXX) $(CXXFLAGS) Driver.o TestBinarySearchTree.o Word.o Indexer.o BinarySearchTree.o -o proj2

Driver.o: Driver.cpp
  $(CXX) $(CXXFLAGS) -c Driver.cpp	

TestBinarySearchTree.o: TestBinarySearchTree.cpp
	$(CXX) $(CXXFLAGS) -c TestBinarySearchTree.cpp

Word.o: Word.h Word.cpp
	$(CXX) $(CXXFLAGS) -c Word.cpp

Indexer.o: Indexer.h Indexer.cpp
	$(CXX) $(CXXFLAGS) -c Indexer.cpp

BinarySearchTree.o: BinarySearchTree.h
	$(CXX) $(CXXFLAGS) -c BinarySearchTree.h

	

clean:
	rm proj2 *o *~

run1:
	./proj2 gsl.txt input1.txt

run2:
	./proj2 gsl.txt input2.txt

val1:
	valgrind ./proj2 gsl.txt input1.txt

val2:
	valgrind ./proj2 gsl.txt input2.txt

  
