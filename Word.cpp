#include "Word.h"
//#include "BinarySearchTree.h"

Word::Word() {
	m_wordText = EMPTY_STR;
	m_isEmpty = true;
	m_count = 0;
}

Word::Word(string newWord, int lineNum) {
	m_wordText = newWord;
	m_lineNumbers.push(lineNum);
	m_isEmpty = false;
	m_count = 1;

}

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

	while (currChar != &line[line.size()]){
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

int Word::GetCount() { return m_count; }

void Word::SetCount(int val) {
	if (val <= 0) { EmptyQueue(); m_wordText = EMPTY_STR; m_count = 0; m_isEmpty = true; }
	else { m_count = val; }

}

void Word::CountWord(int lineNum) {
	SetCount(++m_count);
	if (lineNum != m_lineNumbers.back()) { PushLineNum(lineNum); }
}

bool Word::GetIsEmpty() { return m_isEmpty; }

void Word::SetIsEmpty(bool val) { m_isEmpty = val; }

int Word::GetBackLineNum() {
	if (m_count == 0) { throw UnderflowException("Current word has not been indexed"); }
	return m_lineNumbers.back();
}

int Word::GetFrontLineNum() {
	if (m_count == 0) { throw UnderflowException("Current word has not been indexed"); }
	return m_lineNumbers.front();
}

void Word::PushLineNum(int linenum) {
	if (linenum > 0) {
		m_lineNumbers.push(linenum);
	}

}

string Word::GetWord() {
	if (m_isEmpty) { throw UnderflowException("Current word has not been indexed"); }
	return m_wordText;
}



void Word::SetWord(string source) {
	m_wordText = source;
}


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

bool Word::operator==(Word& source) {
	if (m_wordText != source.m_wordText) { return false; }
	if (m_lineNumbers != source.m_lineNumbers) { return false; }
	if (m_count != source.m_count) { return false; }
	return true;
}

/******************************ERASE WHEN FINSHED*************************************************/
bool Word::operator!=(string& source) {
	if (source[source.size() - 1] == DELIM) {
		source.erase(source.size() - 1);
	}
	if (m_wordText != source) { return true; }
	return false;
}
/******************************ERASE WHEN FINSHED*************************************************/


ostream& operator<<(ostream& out, Word& source) {

	if (!source.GetIsEmpty()) {

		const int MAX_DOTS = 24, SIZE = source.m_wordText.size();
		queue<int> temp = source.m_lineNumbers;

		
		out << source.GetWord();

		// display dots and count
		for (int i = 0; i < MAX_DOTS - SIZE; i++) {
			out << ".";
		}
		out << source.GetCount() << ": ";

		// display linenumbers using a temp copy of queue
		while (!temp.empty()) {
			out << temp.front() << " ";
			temp.pop();
		}
	}


	return out;
}


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
