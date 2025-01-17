#include "function.h"

int main()
{
	// DESIGN CONSOLE BACKGROUND
	CONSOLE_FONT_INFOEX cfi;
	fontSize(cfi, 0, 23);
	// system("Color 0A"); // change background color
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	std::ios::sync_with_stdio(false);
	cin.tie(NULL);
	// INITIALIZE VARIABLES
	Trie trie, stopword;		// tree
	vector<string> history;		// store history search
	vector<string> vt1;			// store file name
	vector<string> vt2;			// store file name
	char* str1 = new char[50];	// store words temporarily
	char* str2 = new char[50];	// store words temporarily
	char* input = new char[50]; // input from user
	title(); // print title
	auto start = high_resolution_clock::now(); 	// time complexity

	// LOAD DATA & STOPWORDS
	cout << "Loading..." << endl;
	trie.getFileName(trie.root, str1, vt1);
	stopword.readStop("stopwords.txt", stopword.root, 0);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	cout << "Loading time: "
		<< duration.count() << " ms" << endl;

	// SEARCH
	cout << "*** Type \"exit\" to exit the program (Want to search for \"exit\"? Enter + type in \"exit\")" << endl << endl;
	cout << "*** 10 Queries supported: " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "1. AND                                      6. FILETYPE(example: filetype: txt)" << endl;
	cout << "2. OR                                       7. INTITLE(example: intitle: beer)" << endl;
	cout << "3. PLUS (put + before the stopword)         8. EXACT(example: \"star wars\")" << endl;
	cout << "4. PRICE (example: camera $500)             9. RANGE(example: camera $100..$500)" << endl;
	cout << "5. HASTAG(example: #handsome)               10. MINUS(example: New -York)" << endl << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << "*** HISTORY SEARCH: " << endl << endl;
	cout << "*** Please enter keyword: ";
	cin.getline(input, 50, '\n');
	cout << endl;

	while (strcmp(input, "exit") != 0)
	{
		while (strcmp(input, "") == 0) // check if user type in nothing
		{
			cout << "Empty!!! Please enter keyword again: ";
			cin.getline(input, 50, '\n');
			cout << endl;
		}
		history.push_back(input);
		trie.QueryOperator(trie.root, input, vt1, stopword.root); // main function: check, search, output query
		cout << endl << "*** ENTER TO CONTINUE ***" << endl;
		cin.get();
		system("CLS");
		title();
		cout << "*** Type \"exit\" to exit the program (Want to search for \"exit\"? Enter + type in \"exit\")" << endl << endl;
		cout << "*** 10 Queries supported: " << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		cout << "  1. AND                                      6. FILETYPE(example: filetype: txt)" << endl;
		cout << "  2. OR                                       7. INTITLE(example: intitle: beer)" << endl;
		cout << "  3. PLUS (put + before the stopword)         8. EXACT(example: \"star wars\") " << endl;
		cout << "  4. PRICE (example: camera $500)             9. RANGE(example: camera $100..$500)" << endl;
		cout << "  5. HASTAG(example: #handsome)               10. MINUS(example: New -York)" << endl << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout << "*** HISTORY SEARCH: " << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		if (history.size() > 5)
			history.erase(history.begin());
		for (int i = 0; i < history.size(); ++i)
			cout << "  > " << history.at(i) << endl;
		cout << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout << "*** Please enter keyword: ";
		cin.getline(input, 50, '\n');
		cout << endl;
	}

	// DELETE POINTERS
	delete[] str1;
	delete[] str2;
	delete[] input;

	return 0;
}