#include "Indexer.h"


Indexer::Indexer() {
	m_dataFile = "";
	m_filterFile = "";

	m_indexBST = nullptr;
	m_filteredBST = nullptr;
}

Indexer::Indexer(string filterFile, string dataFile) {
	m_dataFile = dataFile;
	m_filterFile = filterFile;

	m_indexBST = nullptr;
	m_filteredBST = nullptr;
}


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
	// m_indexBST->printTree();

}

void Indexer::Export(string fileName) {
	if (!m_indexBST->isEmpty()) {
		m_indexBST->Export(fileName);
	}
}

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

BinarySearchTree<Word>& Indexer::FileFilterReader(string filterFile) {
	int lineNum = 1;
	string newWord;
	ifstream file;
	BinarySearchTree<Word>* IndexTree = new BinarySearchTree<Word>;
	file.open(filterFile);
	while (getline(file, newWord)) {
		
		Word temp(newWord, lineNum);
		temp.LowerWord();

		IndexTree->insert(temp);

		lineNum++;
	}
	file.close();
	return *IndexTree;
}

BinarySearchTree<Word>& Indexer::FileWordReader(string wordFile) {
	int lineNum = 1;
	string line = "";
	ifstream file;
	file.open(wordFile.c_str());
	BinarySearchTree<Word>* WordTree = new BinarySearchTree<Word>;
	while (getline(file, line)) {
		FilterLine(line, lineNum, *WordTree);
		lineNum++;
	}

	file.close();
	return *WordTree;
}

void Indexer::InsertWord(string& word, const int& lineNumber, BinarySearchTree<Word>& WordTree) {
	int frontIndex = 0, endIndex;
	char* frontVal = &word[frontIndex], *endVal = nullptr;

	// if (frontVal != nullptr && ispunct(*frontVal) && *frontVal != APOST) { word.erase(frontIndex, frontIndex + 1); }
	if (frontVal != nullptr && ispunct(*frontVal)) { word.erase(frontIndex, frontIndex + 1); }


	if (word.length() != 0) {
		endIndex = word.length() - 1; endVal = &word[endIndex];
		// if (endVal != nullptr && ispunct(*endVal) && *endVal != APOST) { word.erase(endIndex); }
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


void Indexer::FilterLine(string& line, int& lineNumber, BinarySearchTree<Word>& WordTree) {
	// line must contain at least one character
	if (line.size() != 0) {
		int min = 0, maxVal = line.size();
		char* currChar = &line[0], * frontVal = nullptr, * endVal = nullptr;
		string word = "";

		while (currChar != &line[maxVal]) {
			// lowercase curr char 
			if (!ispunct(*currChar) && isupper(*currChar)) {
				*currChar = tolower(*currChar);
			}

			// build word
			/*
			if (*currChar != DELIM && (!ispunct(*currChar) || *currChar == APOST ||
				(*currChar == DASH && currChar != &line[maxVal]) || *currChar == QUOTE) && !isdigit(*currChar)) {
				word.push_back(*currChar);
			}
			*/
			if (*currChar != DELIM && (!ispunct(*currChar) || (*currChar == DASH && currChar != &line[maxVal]) 
				/*|| *currChar == QUOTE*/) && !isdigit(*currChar)) {
				word.push_back(*currChar);
			}

			// word is created
			else if (*currChar == DELIM && word != WORD_SP && word != EMPTY_STR) {
				InsertWord(word, lineNumber, WordTree);
			}

			currChar++;
		}

		if (word != EMPTY_STR) {
			InsertWord(word, lineNumber, WordTree);
		}
		
	}
}

void Indexer::String_To_Char(string source, char char_cpy[]) {
	const int WORD_SIZE = source.length();
	if (source.length() > MAX_CHAR) { throw ArrayIndexOutOfBoundsException("Current file name is too large"); }
	for (int i = 0; i < WORD_SIZE; i++) {
		char_cpy[i] = source[i];
	}
}
