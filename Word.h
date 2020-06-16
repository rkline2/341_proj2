#ifndef WORD_H
#define WORD_H

#include <string>
#include <queue>

class Word {
public:
	// Default Constructor 
	Word();

	// Overloaded Constructor
	Word(string word, int lineNum);

	// Count Word 
	// Increments the word's occurance 
	// Adds the word to the queue if not in the queue
	void CountWord(int lineNum);

	// Return the current word and frequency
	string GetWord();

	bool operator<(Word& RHS);

	Word operator=(Word& RHS);

	friend ostream operator<<(ostream out, Word& source);

private:
	int m_count;
	string m_wordText;
	queue<int> m_lineNumbers;
};



#endif
