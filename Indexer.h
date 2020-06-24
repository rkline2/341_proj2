#ifndef INDEXER_H
#define INDEXER_H

#include <iostream>
#include <fstream>
#include <string>
#include "BinarySearchTree.h"
#include "Exceptions.h"
using namespace std;



class Indexer {
public:
	// Default Constructor 
	Indexer();

	// Overloaded Constructor 
	Indexer(string filterFile, string dataFile);


	// Do Index 
	void DoIndex();

	bool FileExists(char*);

	BinarySearchTree<Word>& FileFilterReader(string);

	BinarySearchTree<Word>& FileWordReader(string);

	void String_To_Char(string, char []);

	void Export(string);

private:

	void FilterLine(string&, int&, BinarySearchTree<Word>&);
	void InsertWord(string& word, const int& lineNumber, BinarySearchTree<Word>& WordTree);

	BinarySearchTree<Word>* m_filteredBST;
	BinarySearchTree<Word>* m_indexBST;
	string m_filterFile = "";
	string m_dataFile = "";

};


#endif
