#include "function.h"

int main()
{
	// DESIGN CONSOLE BACKGROUND
	CONSOLE_FONT_INFOEX cfi;
	fontSize(cfi, 0, 23);
	// system("Color 0A"); // change background color
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

	// INITIALIZE VARIABLES
	Trie trie, stopword;		// tree
	vector<string> history;		// store history search
	vector<string> vt1;			// store file name
	vector<string> vt2;			// store file name
	char* str1 = new char[50];	// store words temporarily
	char* str2 = new char[50];	// store words temporarily
	char* input = new char[50]; // input from user
	clock_t start = clock();	// time complexity
	title(); // print title

	// LOAD DATA & STOPWORDS
	cout << "Loading..." << endl;
	trie.getFileName(trie.root, str1, vt1);
	stopword.readWord("stopwords.txt", stopword.root, str2, 0);
	cout << "Loading time: " << (double)(clock() - start) / CLOCKS_PER_SEC << endl << endl;

	// SEARCH
	cout << "*** Type \"exit\" to exit the program (Want to search for \"exit\"? Enter + type in \"exit\")" << endl << endl;
	cout << "*** 10 Queries supported: " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "1. AND                                      6. FILETYPE(example: filetype: txt)" << endl;
	cout << "2. OR                                       7. INTITLE(example: intitle: beer)" << endl;
	cout << "3. PLUS (put + before the stopword)         8. EXACT(example: \"star wars\")" << endl;
	cout << "4. PRICE (example: camera $400)             9. RANGE(example: camera $100..$500)" << endl;
	cout << "5. HASTAG(example: #MileyCyrus)            10. MINUS(example: New -York)" << endl << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout<< "*** HISTORY SEARCH: " << endl << endl;
	cout << "*** Please enter keyword: ";
	cin.getline(input, 50, '\n');
	cout << endl;

	while (strcmp(input, "exit") != 0)
	{
		history.push_back(input);
	}

	// DELETE POINTERS
	delete[] str1;
	delete[] str2;
	delete[] input;

	return 0;
}