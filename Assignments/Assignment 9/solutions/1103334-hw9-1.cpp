#include <iostream>
using namespace::std;
#include <fstream>
#include <cstring>

// input all words from the file Dictionary.txt, and put them to the array "dictionary"
void readDictionary(char(*dictionary)[21], int& numDicWords);

// return true if and only if wordToCheck == dictionary[ i ] for some i
bool legal(char* wordToCheck, char(*dictionary)[21], int numDicWords);

// Find every word w in the array "dictionary" which satisfies two conditions:
// 1. the length of w is equal to the length of wordToCheck, and
// 2. wordToCheck and w are different on exactly one character.
// Put these  .
void spellCheck1(char* wordToCheck, char(*dictionary)[21], int numDicWords, char(*&result)[21], int& numResult);

// Find every word w in the array "dictionary" which satisfies two conditions:
// 1. the length of w is one greater than the length of wordToCheck, and
// 2. wordToCheck is equal to the substring obtained by deleting a character from w.
// Put these words into the array "result".
void spellCheck2(char* wordToCheck, char(*dictionary)[21], int numDicWords, char(*&result)[21], int& numResult);

// Find every word w in the array "dictionary" which satisfies two conditions:
// 1. the length of w is one less than the length of wordToCheck, and
// 2. w is equal to the substring obtained by deleting a character from wordToCheck.
// Put these words into the array "result".
void spellCheck3(char* wordToCheck, char(*dictionary)[21], int numDicWords, char(*&result)[21], int& numResult);

// find the words in the array "dictionary" whose length is equal to the last parameter "length",
// and puts these words into the array "words"
void findWords(char(*&words)[21], int& numWords, char(*dictionary)[21], int numDicWords, int length);

// output all words in the array "result" to the file Result.txt
void saveWords(char(*result)[21], int numResult);

int main()
{
	srand(1);

	int numDicWords = 0;
	char(*dictionary)[21] = new char[40000][21];

	readDictionary(dictionary, numDicWords);

	char wordToCheck[21];
	int numResult = 0;
	char(*result)[21] = new char[3000][21];
	for (int i = 0; i < 10; i++)
	{

		strcpy_s(wordToCheck, 21, dictionary[rand() + numDicWords - 32768]);
		int length = strlen(wordToCheck);
		for (int j = rand() % length; j < length; j++)
			wordToCheck[j] = wordToCheck[j + 1];

		if (legal(wordToCheck, dictionary, numDicWords))
			cout << wordToCheck << " is a legal english word.\n";
		else
		{
			cout << wordToCheck << endl;

			strcpy_s(result[numResult++], 21, wordToCheck);

			spellCheck1(wordToCheck, dictionary, numDicWords, result, numResult);
			spellCheck2(wordToCheck, dictionary, numDicWords, result, numResult);
			spellCheck3(wordToCheck, dictionary, numDicWords, result, numResult);

			strcpy_s(result[numResult++], 21, "");
		}
	}

	saveWords(result, numResult);

	delete[] dictionary;
	delete[] result;

	system("pause");
}

bool legal(char* wordToCheck, char(*dictionary)[21], int numDicWords)
{
	for (int i = 0; i < numDicWords; i++)
		if (strcmp(dictionary[i], wordToCheck) == 0)
			return true;
	return false;
}

void readDictionary(char(*dictionary)[21], int& numDicWords)
{
	ifstream inFile("Dictionary.txt", ios::in);

	if (!inFile)
	{
		cout << "File couldn't be opened!!!" << endl;
		exit(1);
	}

	numDicWords = -1;
	while (!inFile.eof())
	{
		numDicWords++;
		inFile >> dictionary[numDicWords];
	}
	inFile.close();
}

void spellCheck1(char* wordToCheck, char(*dictionary)[21],
	int numDicWords, char(*&result)[21], int& numResult)
{
	int length = strlen(wordToCheck);
	int numWords = 0;
	char(*words)[21] = 0;

	findWords(words, numWords, dictionary, numDicWords, length);

	char buffer1[21];
	char buffer2[21];
	strcpy_s(buffer2, wordToCheck);
	for (int i = 0; i < numWords; i++)
	{
		int differNumber = 0;
		strcpy_s(buffer1, words[i]);
		for (int j = 0; j < length; j++)
		{
			if (buffer1[j] != buffer2[j])
				differNumber++;
		}

		if (differNumber == 1)
			strcpy_s(result[numResult++], buffer1);
	}


	delete[] words;
}

void spellCheck2(char* wordToCheck, char(*dictionary)[21],
	int numDicWords, char(*&result)[21], int& numResult)
{
	int length = strlen(wordToCheck) + 1;
	int numWords = 0;
	char(*words)[21] = 0;

	findWords(words, numWords, dictionary, numDicWords, length);

	char buffer[21];
	for (int i = 0; i < numWords; i++)
	{

		strcpy_s(buffer, words[i]);
		for (int j = 0; j < length; j++)
		{
			int notSame = 0;
			for (int k = 0, comp = 0; k < length; comp++, k++) //wordtoCheck
			{
				if (j == comp)
					comp++;

				if (buffer[comp] != wordToCheck[k])
					notSame++;
			}
			if (notSame == 0)
			{
				strcpy_s(result[numResult++], buffer);
				break;
			}
		}
	}

}

void spellCheck3(char* wordToCheck, char(*dictionary)[21],
	int numDicWords, char(*&result)[21], int& numResult)
{
	int length = strlen(wordToCheck) - 1;
	int numWords = 0;
	char(*words)[21] = 0;
	//For example, if str is the string tabe, 
	//	the word tab satisfies conditions eand f,
	findWords(words, numWords, dictionary, numDicWords, length);

	char buffer[21];
	for (int i = 0; i < numWords; i++)
	{
		strcpy_s(buffer, words[i]);
		for (unsigned int j = 0; j <= strlen(wordToCheck); j++)  //4 tabe 
		{
			int notFound = 0;
			for (int k = 0, comp = 0; k < length; comp++, k++)  //3 tab
			{
				if (comp == j)
					comp++;
				if (buffer[k] != wordToCheck[comp])
					notFound++;
			}
			if (notFound == 0)
			{
				strcpy_s(result[numResult++], buffer);
				break;
			}
		}
	}

	delete[] words;
}


void findWords(char(*&words)[21], int& numWords,
	char(*dictionary)[21], int numDicWords, int length)
{
	for (int i = 0; i < numDicWords; i++)
		if (strlen(dictionary[i]) == length)
			numWords++;

	words = new char[numWords][21];

	numWords = 0;
	for (int i = 0; i < numDicWords; i++)
		if (strlen(dictionary[i]) == length)
		{
			strcpy_s(words[numWords], 21, dictionary[i]);
			numWords++;
		}
}
void saveWords(char(*result)[21], int numResult)
{
	ofstream outFile("Result.txt", ios::out);

	if (!outFile)
	{
		cout << "File could not be opened" << endl;
		exit(1);
	}


	for (int i = 0; i < numResult; i++)
	{
		//cout << result[i] << endl;
		outFile << result[i] << endl;;
	}

	outFile.close();


}