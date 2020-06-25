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
	// Name: Indexer Default Constructor 
	// Description: Creates an empty Indexer object
	// Pre-Conditions: None  
	// Post-Conditions: Creates an empty Indexer object
	Indexer();

	// Name: Indexer Overloaded Constructor 
	// Description: Creates an Indexer object
	// Pre-Conditions: Txt file names given  
	// Post-Conditions: Creates an Indexer object
	Indexer(string filterFile, string dataFile);

	// Name: Indexer Destructor 
	// Description: Deletes Indexer object
	// Pre-Conditions: Indexer object exists  
	// Post-Conditions: Deletes and clears all BSTs and filenames 
	~Indexer();


	// Name: DoIndex
	// Description: Creates an Index and Filter BST
	// based on the .txt files and displays the Words in the BST
	// Pre-Conditions: Filter and Index BST exists. Index filename is valid  
	// Post-Conditions: Creates an Index and Filter BST and displays the Index BST
	void DoIndex();

	// Name: FileExists
	// Description: Tests if a .txt file exists or not 
	// Pre-Conditions: None 
	// Post-Conditions: Returns a bool depending if the .txt file exists
	bool FileExists(char*);

	// Name: FileFilterReader
	// Description: Reads in a .txt file meant to build a Filter BST 
	// Pre-Conditions: .txt file exists 
	// Post-Conditions: Returns a BST for m_filteredBST
	BinarySearchTree<Word>& FileFilterReader(string);

	// Name: FileWordReader
	// Description: Reads in a .txt file meant to build a Index BST 
	// Pre-Conditions: .txt file exists 
	// Post-Conditions: Returns a BST for m_indexBST
	BinarySearchTree<Word>& FileWordReader(string);

	// Name: String_To_Char
	// Description: Creates a char array based on the 
	// given string value 
	// Pre-Conditions: Parameters are valid  
	// Post-Conditions: Deep copy a string value to a char array
	void String_To_Char(string, char[]);

	// Name: Export
	// Description: Writes a Index BST to a .txt file 
	// Pre-Conditions: BST exists 
	// Post-Conditions: Writes Index BST to a .txt value 
	void Export();

private:
	// Name: FilterLine
	// Description: Given a line from a .txt file, splits and 
	// lowercases every word from the line and removes punctuation 
	// Pre-Conditions: .txt file exists
	// Post-Conditions: Splits and filters a line from a .txt file
	void FilterLine(string&, int&, BinarySearchTree<Word>&);
	
	// Name: InsertWord
	// Description: Inserts a Word into the Index BST
	// Pre-Conditions: BST exists and Word is valid
	// Post-Conditions: Inserts word into m_indexBST
	void InsertWord(string& word, const int& lineNumber, BinarySearchTree<Word>& WordTree);

	BinarySearchTree<Word>* m_filteredBST; // Filtered BST
	BinarySearchTree<Word>* m_indexBST; // Index BST
	string m_filterFile = ""; // Filtered BST .txt filename
	string m_dataFile = ""; // Index BST .txt filename

};


#endif
