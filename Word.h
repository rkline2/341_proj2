#ifndef WORD_H
#define WORD_H

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <iomanip> // for fill only
#include "dsexceptions.h"

using namespace std;

const string EMPTY_STR = "", WORD_SP = " ", END_FILE_NAME = ".txt";
const char APOST = '\'', QUOTE = '"', DASH = '-', DELIM = ' ', FILL_VAL = '.', UNDER_S = '_';
const int MAX_CHAR = 256, MAX_DOTS = 24, MIN_FILE_NUM = 5, ASCII_MIN_CHAR = -1, ASCII_MAX_CHAR = 255;

class Word {
public:
	// Name: Word Default Constructor 
	// Description: Creates an empty Word
	// Pre-Conditions: None  
	// Post-Conditions: Creates an empty Word
	Word();

	// Name: Word Overloaded Constructor 
	// Description: Creates a new Word
	// Pre-Conditions: String and int values must be valid  
	// Post-Conditions: Given a word-text and 
	// linenumber, creates a new word
	Word(string, int);

	// Name: Word Destructor 
	// Description: Deletes Word object
	// Pre-Conditions: Word exists  
	// Post-Conditions: Clears out m_variables associated with Word 
	~Word();

	// Name: GetCount  
	// Description: Returns the amount of times 
	// the current word has been recorded from a given file
	// Pre-Conditions: Word exists
	// Post-Conditions: Returns m_count
	int GetCount();

	// Name: GetIsEmpty  
	// Description: Returns if the current word is empty or not
	// Pre-Conditions: Word exists
	// Post-Conditions: Returns m_isEmpty
	bool GetIsEmpty();

	// Name: Line Number Getters
	// Description: Returns the front/end of the linenumber queue
	// Pre-Conditions: Word exists
	// Post-Conditions: Returns front/back of linenumber queue
	int GetBackLineNum();
	int GetFrontLineNum();

	// Name: Wordtext accessors and mutators
	// Description: Returns/sets m_wordText. CountWord 
	// will push a new line number to the queue 
	// if the line number doesn't exist in the queue  
	// Pre-Conditions: Word exists
	// Post-Conditions: Returns/sets m_wordText
	string GetWord();
	void CountWord(int);
	void LowerWord();
	
	// Temp function
	// void SetTestWord(string);

	// Name: Word Overloaded Operators 
	// Description: Compares two Word values based 
	// on which operator is being overloaded
	// Pre-Conditions: Word exists
	// Post-Conditions: Returns a bool/word/output based on the operator
	bool operator<(const Word& RHS) const {
		if (m_wordText < RHS.m_wordText) { return true; }
		return false;
	}
	Word& operator=(Word& RHS);
	bool operator==(Word& RHS);
	bool operator!=(const Word& RHS);
	friend ostream& operator<<(ostream& out, Word& source);


private:
	// Name: Count Mutator
	// Description: Sets the amount of times 
	// the current word has been recorded from a given file
	// Pre-Conditions: Pass in a valid int Word exists
	// Post-Conditions: Sets m_count
	void SetCount(int);

	// Name: IsEmpty Mutator
	// Description: Sets the current word being empty or not
	// Pre-Conditions: Pass in a bool and Word exists
	// Post-Conditions: Sets m_isEmpty true or false
	void SetIsEmpty(bool);

	// Name: Word-text Mutator
	// Description: Sets the current word-text
	// Pre-Conditions: Pass in a valid string and Word exists
	// Post-Conditions: Sets m_wordText 
	void SetWord(string);
	void PushLineNum(int);

	// Name: EmptyQueue
	// Description: Removes all of the nodes in the line number queue 
	// Pre-Conditions: Line number queue exists
	// Post-Conditions: Deletes m_lineNumbers
	void EmptyQueue() {
		while (!m_lineNumbers.empty()) {
			m_lineNumbers.pop();
		}
		m_isEmpty = true;
	}

	int m_count; // Number of times the word has been recorded
	string m_wordText; // String value of the recorded word from the txt file
	bool m_isEmpty; // Determines if the word is empty or not 
	queue<int> m_lineNumbers; // Queue of linenumbers 
};

#endif
