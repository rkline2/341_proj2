#ifndef WORD_H
#define WORD_H

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "dsexceptions.h"

using namespace std;

const string EMPTY_STR = "", WORD_SP = " ";
const char APOST = '\'', QUOTE = '"', DASH = '-', DELIM = ' ';
const int MAX_CHAR = 256;

class Word {
public:

	Word();

	// Overloaded Constructor
	Word(string, int);

	int GetCount();


	bool GetIsEmpty();

	int GetBackLineNum();
	int GetFrontLineNum();

	// Count Word 
	// Increments the word's occurance 
	// Adds the line to the queue if not in the queue
	void CountWord(int);

	// Return the current word and frequency
	string GetWord();

	void LowerWord();

	void SetTestWord(string);

	bool operator<(const Word&RHS)const {
		if (m_wordText < RHS.m_wordText) { return true; }
		return false;
	}
	

	Word& operator=(Word& RHS);

	bool operator==(Word& RHS);

	bool operator!=(string&);

	friend ostream& operator<<(ostream& out, Word& source);


private:
	void SetCount(int);
	void SetIsEmpty(bool);
	void SetWord(string);
	void PushLineNum(int);

	

	void EmptyQueue() {
		while (!m_lineNumbers.empty()) {
			m_lineNumbers.pop();
		}
		m_isEmpty = true;
	}

	int m_count;
	string m_wordText;
	bool m_isEmpty;
	queue<int> m_lineNumbers;
};



#endif
