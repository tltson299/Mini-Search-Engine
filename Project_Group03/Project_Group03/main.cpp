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

	// LOAD DATA & STOPWORDS
	cout << "Loading..." << endl;
	trie.getFileName(trie.root, str1, vt1);
	stopword.readWord("stopwords.txt", stopword.root, str2, 0);
	cout << "Loading time: " << (double)(clock() - start) / CLOCKS_PER_SEC; cout << endl << endl;

	return 0;
}