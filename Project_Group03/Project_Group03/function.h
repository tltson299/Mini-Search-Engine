#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstring>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <time.h>
#include <algorithm>
#include <filesystem>
#include <sstream>
#include <cwchar>
#include <windows.h>
using namespace std;
using namespace std::filesystem;

// NODE
class Node
{
public:
	bool isLeaf;
	vector<int> myv;
	map<char, Node*> mapkey;
};

// TREE
class Trie
{
public:
	// build and delete trie functions
	~Trie()
	{
		deleteTrie(root);
	}
	Node* root = nullptr;
	Node* createNode();
	void insert(Node*& root, string str, int i);
	void readWord(string ptr, Node*& root, int i, string word);
	void getFileName(Node*& root, char* str, vector<string>& vt);
	void deleteTrie(Node*& root);
	// main algorithm functions
	Node* getFile(Node* root, char* str);
	void removeStopWord(vector<string>& store, Node* root2);
	// queries functions
	void commonVector(vector<int> inputvt, vector<int>& common);
	void getQueryAnd(Node* root, vector<string>& store, char*& str2, vector<int>& common, int& countN, int qt);
	void getQueryOr(Node* root2, vector<string>& store, char*& str2, vector<int>& common, int& countN);
	bool queryPrice(vector<string> input);
	bool queryHastag(vector<string> input);
	bool queryIntitle(string input);
	bool queryFileType(string input);
	bool queryExact(vector<string> input);
	bool queryRange(vector<string>& input, string& start, string& end, string& sim);
	bool queryMinus(vector<string>& input, vector<string>& minus);
	void QueryOperator(Node* root, char* str, vector<string>& vt, Node* root2);
	// output functions
	void outPutResult(string fileName, vector<string> input, int& count, bool exact, bool intitle);
	void ouputVectorEx(vector<string> mys, string filename, bool& found, vector<string> highlight, int pos);
	void ouputVector(vector<string> mys, string filename, bool& found, vector<string> highlight);
	bool checkString(string input, string word);
	bool checkOnVector(vector<string> input, string word);
	bool checkIntOnVector(vector<int>minus, int input);
	void checkPlus(vector<string>& input, Node* root2, vector<string>& result);
};

// OTHER FUNCTIONS
void title();
void lowerChar(char*& str);
void lowerString(string& str);
bool isDuplicate(vector<int> a, int b);
vector<int> mergeVector(vector<int> a, vector<int> b);
void fontSize(CONSOLE_FONT_INFOEX& cfi, int x, int y);

#endif  // !_FUNCTION_H_