/**************************************************************
** File:    Indexer.cpp
** Project: CMSC 341 - Project 2 - Index Creator
** Author : Rooklyn Kline
** Date   : 25-June-2020
** Section: Lecture-02
** E-mail:  rkline2@umbc.edu
**
** Description:
**
** This file primarily focuses on filtering and storing
** words from the given files to the m_filter and
** m_data BSTs. Words from the data BST will only be stored if
** the word isn't located in the m_filter BST.
**
*************************************************************/
#include "Indexer.h"

// Name: Indexer (default constructor)
// Creates an empty Indexer object
Indexer::Indexer() {
	m_dataFile = "";
	m_filterFile = "";

	m_indexBST = nullptr;
	m_filteredBST = nullptr;
}

// Name: Indexer (overloaded constructor)
// Creates an Indexer object
Indexer::Indexer(string filterFile, string dataFile) {
	m_dataFile = dataFile;
	m_filterFile = filterFile;

	m_indexBST = nullptr;
	m_filteredBST = nullptr;
}
// Name: ~Indexer (destructor)
// Deletes and clears all BSTs and filenames  
Indexer::~Indexer() {
	delete m_filteredBST; delete m_indexBST;
	m_filteredBST = nullptr; m_indexBST = nullptr;

	m_filterFile.clear(); m_dataFile.clear();
}

// Name: DoIndex
// Creates an Index and Filter BST and displays the Index BST
void Indexer::DoIndex() {
	char word_file[MAX_CHAR] = { NULL }, filter_file[MAX_CHAR] = { NULL };
	try {
		String_To_Char(m_dataFile, word_file); String_To_Char(m_filterFile, filter_file);
	}
	catch (ArrayIndexOutOfBoundsException& e) {
		cerr << "Error: " << e.what() << endl;
	}

	bool word_file_exists = FileExists(word_file), filter_file_exists = FileExists(filter_file);
	// files does not exist 
	if (!word_file_exists) { throw Exceptions("Word file not found"); }

	if (word_file_exists && filter_file_exists) {
		m_filteredBST = &FileFilterReader(m_filterFile);
		m_indexBST = &FileWordReader(m_dataFile);
	}

	else {
		m_indexBST = &FileWordReader(m_dataFile);
	}
	Export();
	//m_indexBST->printTree();

}

// Name: FileExists
// Given a char*, returns a bool depending if the .txt file exists
bool Indexer::FileExists(char* fileName) {
	string line = ""; bool doesExist = false; ifstream file;
	file.open(fileName);
	if (file.good()) {
		getline(file, line);
		// file cannot be empty 
		if (line.size() > 0) {
			doesExist = true; line.clear();
		}
	}

	file.close();
	return doesExist;
}

// Name: FileFilterReader
// Given a filename, returns a BST for m_filteredBST
BinarySearchTree<Word>& Indexer::FileFilterReader(string filterFile) {
	int lineNum = 1;
	string newWord;
	ifstream file;
	BinarySearchTree<Word>* IndexTree = new BinarySearchTree<Word>;
	file.open(filterFile);
	while (getline(file, newWord)) {
		if (newWord.size() > 0) {
			Word temp(newWord, lineNum);
			temp.LowerWord();

			IndexTree->insert(temp);
		}
		lineNum++;
	}
	file.close();
	return *IndexTree;
}

// Name: FileWordReader
// Given a filename, returns a BST for m_indexBST
BinarySearchTree<Word>& Indexer::FileWordReader(string wordFile) {
	int lineNum = 1;
	string line = "";
	ifstream file;
	file.open(wordFile.c_str());
	BinarySearchTree<Word>* WordTree = new BinarySearchTree<Word>;
	while (getline(file, line)) {
		// does not accept blank lines
		if (line.size() > 0) {
			FilterLine(line, lineNum, *WordTree);
		}
		lineNum++;
	}

	file.close();
	return *WordTree;
}

// Name: InsertWord
// Given a string, int and BST, inserts a word into m_indexBST
void Indexer::InsertWord(string& word, const int& lineNumber, BinarySearchTree<Word>& WordTree) {
	int frontIndex = 0, endIndex;
	char* frontVal = &word[frontIndex], * endVal = nullptr;

	if (frontVal != nullptr && ispunct(*frontVal)) { word.erase(frontIndex, frontIndex + 1); }


	if (word.length() != 0) {
		endIndex = word.length() - 1; endVal = &word[endIndex];

		if (endVal != nullptr && ispunct(*endVal)) { word.erase(endIndex); }

		Word temp(word, lineNumber);


		// filtered BST is empty
		if (word != EMPTY_STR && m_filteredBST->isEmpty()) {
			WordTree.Insert_To_Word_BST(temp, lineNumber);
		}

		// word cannot be in filtered BST
		else if (word != EMPTY_STR && !m_filteredBST->contains(temp)) {
			WordTree.Insert_To_Word_BST(temp, lineNumber);
		}
	}
	word.clear();
}

// Name: FilterLine
// Given a string, int, BST, Splits and filters a line from a .txt file
void Indexer::FilterLine(string& line, int& lineNumber, BinarySearchTree<Word>& WordTree) {
	// line must contain at least one character
	if (line.size() != 0) {
		char* currChar = &line[0]; string word = "";
		int  maxVal = line.size();

		while (currChar != &line[maxVal]) {
			// must be a valid char
			if (*currChar >= ASCII_MIN_CHAR && *currChar <= ASCII_MAX_CHAR) {
				// lowercase curr char 
				if (!ispunct(*currChar) && isupper(*currChar)) {
					*currChar = tolower(*currChar);
				}

				// build word
				if (*currChar != DELIM && (!ispunct(*currChar) || (*currChar == DASH && currChar != &line[maxVal]))
					&& !isdigit(*currChar)) {
					word.push_back(*currChar);
				}


				// word is created
				else if ((*currChar == DELIM || *currChar == APOST) && word != WORD_SP && word != EMPTY_STR) {
					InsertWord(word, lineNumber, WordTree);
				}
			}
			currChar++;
		}

		if (word != EMPTY_STR) {
			InsertWord(word, lineNumber, WordTree);
		}

	}
}

// Name: String_To_Char
// Given a string and char arr, deep copies the string value to a char array
void Indexer::String_To_Char(string source, char char_cpy[]) {
	const int WORD_SIZE = source.length();
	if (source.length() > MAX_CHAR) { throw ArrayIndexOutOfBoundsException("Current file name is too large"); }
	for (int i = 0; i < WORD_SIZE; i++) {
		char_cpy[i] = source[i];
	}
}

// Name: Export
// Writes Index BST to a .txt value
void Indexer::Export() {
	string fileName = "", endFile = ""; int start = 5, nameSize = 0; bool isValid = false;
	while (!isValid) {
		isValid = true; endFile.clear(); fileName.clear(); nameSize = 0;
		cout << "Enter a filename to export data: "; cin >> fileName;
		nameSize = fileName.size();

		for (string::iterator it = fileName.begin(); it != fileName.end(); ++it) {

			// data is not valid
			if ((ispunct(*it) || isdigit(*it)) && (*it != DASH && *it != FILL_VAL && *it != UNDER_S)) { isValid = false; }

			// pushes the last 4 chars
			if (isValid && nameSize > start && it > fileName.end() - start) { endFile.push_back(*it); }
		}
	}
	if (endFile != END_FILE_NAME) { fileName += END_FILE_NAME; }
	m_indexBST->Export(fileName);
}
