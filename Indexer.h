#ifndef INDEXER_H
#define INDEXER_H
#include <string>
#include "BinarySearchTree.h"

class Indexer {
public:
	// Default Constructor 
	Indexer();

	// Overloaded Constructor 
	Indexer(string filterFile, string dataFile);

	// Do Index 
	void DoIndex();



private:
	BinarySearchTree<Word> m_filteredBST;
	BinarySearchTree<Word> m_indexBST;
	string m_filterFile = "";
	string m_dataFile = "";

};


#endif
