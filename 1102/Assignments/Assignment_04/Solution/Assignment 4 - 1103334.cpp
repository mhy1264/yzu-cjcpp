#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

#include <cstring>
#include <ctime>

#include "SpellCheck.h"

// input all words from the file Dictionary.txt, and put them to the vector "dictionary"
void readDictionary(vector& dictionary);

// return true if and only if wordToCheck == dictionary[ i ] for some i
bool legal(string wordToCheck, vector dictionary);

int main()
{
	srand(static_cast<int>(time(0)));
	vector dictionary;

	readDictionary(dictionary);

	string wordToCheck;
	SpellCheck spellCheck;
	for (int i = 0; i < 20; i++)
	{
		wordToCheck = dictionary[rand() + dictionary.size() - 32768]; // skip short words

		//cout << "inital size" << wordToCheck.size() << endl;
		wordToCheck.erase(rand() % wordToCheck.size(), 1);
		//cout << "find size" << wordToCheck.size() << endl;
		if (!legal(wordToCheck, dictionary))
		{
			cout << "Word to check: " << wordToCheck.c_str() << endl;


			spellCheck.equalLength(wordToCheck, dictionary);
			spellCheck.shorter(wordToCheck, dictionary);
			spellCheck.longer(wordToCheck, dictionary);

			spellCheck.output();
			spellCheck.clear();
		}
	}

	system("pause");
}

void readDictionary(vector& dictionary)
{
	int i = 0;
	ifstream inFile("Dictionary.txt", ios::in);
	if (!inFile)
	{
		cout << "Dictionary.txt couldn't be opened" << endl;
		exit(1);
	}
	int size = 1;

	while (!inFile.eof())
	{
		char buffer [100];

		inFile >> buffer;

		int size = 0;
		for (int i = 0; buffer[i] != '\0'; i++)
			size++;
		//cout << "Loading #" << i++ << " "<< buffer << " size = "<<size <<endl;

		string temp(buffer ,size+1);

		dictionary.push_back(temp);

	}
	dictionary.pop_back();
	inFile.close();
	cout << dictionary.size() << endl;

}

bool legal(string wordToCheck, vector dictionary)
{
	for (size_t i = 0; i < dictionary.size(); i++)
		if (dictionary[i] == wordToCheck)
			return true;
	return false;
}