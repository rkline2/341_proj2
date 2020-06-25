/**************************************************************
** File:    Word.cpp
** Project: CMSC 341 - Project 2 - Index Creator
** Author : Rooklyn Kline
** Date   : 25-June-2020
** Section: Lecture-02
** E-mail:  rkline2@umbc.edu
**
** Description:
**
** This file primarily focuses on creating the templated 
** variable "Word" which will be stored in a node in a BST. 
** Each variable will contain the word itself, the amount of
** times the word has been recorded (m_count) and a queue
** of the line numbers where the word has been recorded. 
**
*************************************************************/
#include "Word.h"

// Name: Word (default constructor)
// Creates an empty Word
Word::Word() {
	m_wordText = EMPTY_STR;
	m_isEmpty = true;
	m_count = 0;
}

// Name: Word (overloaded constructor)
// Given a word-text and linenumber, creates a new word
Word::Word(string newWord, int lineNum) {
	m_wordText = newWord;
	m_lineNumbers.push(lineNum);
	m_isEmpty = false;
	m_count = 1;

}

// Name: ~Word() (destructor)
// Deletes linenumber queue and all member variables  
Word::~Word() {
	SetCount(0);
}

// Name: GetCount
// Returns m_count
int Word::GetCount() { 
	if (m_isEmpty) { throw UnderflowException("Current word has not been indexed"); }
	return m_count; 
}

// Name: SetCount
// Given an int, sets m_count
void Word::SetCount(int val) {
	if (val <= 0) { EmptyQueue(); m_wordText = EMPTY_STR; m_count = 0; m_isEmpty = true; }
	else { m_count = val; }

}

// Name: GetIsEmpty
// Retuns m_isEmpty 
bool Word::GetIsEmpty() { return m_isEmpty; }

// Name: SetIsEmpty
// Given a bool, sets m_isEmpty
void Word::SetIsEmpty(bool val) { 
	if (val == true) { EmptyQueue(); m_wordText = EMPTY_STR; m_count = 0; m_isEmpty = true; }
	else { m_isEmpty = false; }
}

// Name: GetBackLineNum
// Returns the back of the m_lineNumbers queue
int Word::GetBackLineNum() {
	if (m_count == 0) { throw UnderflowException("Current word has not been indexed"); }
	return m_lineNumbers.back();
}

// Name: GetFrontLineNum
// Returns the front of the m_lineNumbers queue
int Word::GetFrontLineNum() {
	if (m_count == 0) { throw UnderflowException("Current word has not been indexed"); }
	return m_lineNumbers.front();
}

// Name: PushLineNum
// Given an int, pushes the value to the front of m_lineNumbers
void Word::PushLineNum(int linenum) {
	if (linenum > 0) {
		m_lineNumbers.push(linenum);
	}

}

// Name: GetWord
// Returns m_wordText if the word exists 
string Word::GetWord() {
	if (m_isEmpty) { throw UnderflowException("Current word has not been indexed"); }
	return m_wordText;
}

// Name: SetWord
// Given a string, sets m_wordText
void Word::SetWord(string source) {
	m_wordText = source;
}

// Name: CountWord
// Given a int, increments m_count and pushes 
// the given int to m_lineNum if necessary 
void Word::CountWord(int lineNum) {
	SetCount(++m_count);
	if (lineNum != m_lineNumbers.back()) { PushLineNum(lineNum); }
}

// Name: LowerWord
// Lowercase m_wordText
void Word::LowerWord() {
	// word must be at least 1 char
	if (m_wordText.size() > 0) {
		int endIndex = m_wordText.length() - 1;
		int frontIndex = 0, i = 0, middleVal = endIndex / 2;
		char* frontVal = &m_wordText[frontIndex], * endVal = &m_wordText[endIndex];

		// removes punctuation
		if (ispunct(*frontVal) && *frontVal != APOST) { m_wordText.erase(frontIndex, endIndex + 1); }
		if (ispunct(*endVal) && *endVal != APOST) { m_wordText.erase(endIndex); }

		// lowercase word
		while (i < middleVal) {
			if (isupper(*frontVal)) {
				*frontVal = tolower(*frontVal);
			}

			if (isupper(*endVal)) {
				*endVal = tolower(*endVal);
			}

			++frontVal;
			--endVal;
			i++;
		}

		// length of the word is odd 
		if ((endIndex + 1) % 2 == 1) {
			if (isupper(*frontVal)) {
				*frontVal = tolower(*frontVal);
			}

			if (isupper(*endVal)) {
				*endVal = tolower(*endVal);
			}
		}
	}

}
/*
// Name: SetTestWord
// Creates a Word read from an Output txt
void Word::SetTestWord(string line) {
	const char TEST_DELIM = '.', END_COUNT = ':'; char* currChar = &line[0];
	string testWord = "", string_num = "";

	while (*currChar != TEST_DELIM && !isdigit(*currChar)) {
		testWord.push_back(*currChar);
		currChar++;
	}
	SetWord(testWord);
	testWord.clear();

	while (!isdigit(*currChar)) {
		currChar++;
	}
	while (*currChar != END_COUNT) {
		if (isdigit(*currChar)) {
			string_num.push_back(*currChar);
		}
		currChar++;
	}
	SetCount(stoi(string_num));
	string_num.clear();

	while (currChar != &line[line.size()]) {
		if (isdigit(*currChar)) {
			string_num.push_back(*currChar);
		}

		if (!isdigit(*currChar) && string_num.size() > 0) {
			PushLineNum(stoi(string_num));
			string_num.clear();
		}

		currChar++;
	}
	if (string_num.size() > 0) {
		PushLineNum(stoi(string_num));
	}
}
*/

// Name: operator =
// Given a Word, creates a deep copy of the given word  
Word& Word::operator=(Word& source) {
	if (this != &source) {
		// clears out old word
		SetCount(NULL);

		// deep copies values when the source is not empty 
		if (!source.m_isEmpty) {
			m_lineNumbers = source.m_lineNumbers;
			SetWord(source.m_wordText);
			SetIsEmpty(false);
		}
	}

	return *this;
}

// Name: operator ==
// Given a Word, returns a bool depending
// if the given word is the same word as *this
bool Word::operator==(Word& source) {
	if (m_wordText != source.m_wordText) { return false; }
	if (m_lineNumbers != source.m_lineNumbers) { return false; }
	if (m_count != source.m_count) { return false; }
	return true;
}

// Name: operator !=
// Given a Word, returns a bool depending
// if the given word is NOT the same word as *this
bool Word::operator!=(const Word& source) {
	if (m_wordText != source.m_wordText) { return true; }
	if (m_count != source.m_count) { return true; }
	if (m_lineNumbers != source.m_lineNumbers) { return true; }
	if (m_isEmpty != source.m_isEmpty) { return true; }
	return false;
}

// Name: operator <<
// Given a Word, displays the given word 
ostream& operator<<(ostream& out, Word& source) {

	if (!source.GetIsEmpty()) {
		queue<int> temp = source.m_lineNumbers;
		int width = MAX_DOTS - source.m_wordText.size();
		
		out << source.GetWord();
		
		// display dots and count
		out << setfill(FILL_VAL) << setw(width);

		out << source.GetCount() << ": ";

		// display linenumbers using a temp copy of queue
		while (!temp.empty()) {
			out << temp.front() << " ";
			temp.pop();
		}
	}


	return out;
}
