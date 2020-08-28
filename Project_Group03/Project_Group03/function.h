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
	Node* root = nullptr;
	// build and delete trie function
	Node* createNode();
	void insert(Node*& root, char* str, int i);
	void readWord(string ptr, Node*& root, char* str, int i);
	void getFileName(Node*& root, char* str, vector<string>& vt);
	void deleteTrie(Node*& root);
	//main algorithm function
	Node* getFile(Node* root, char* str);
	void removeStopWord(vector<string>& store, Node* root2);
	//Queries functions
	void commonVector(vector<int> inputvt, vector<int>& common);
	//output functions
	void ouputVector(vector<string> mys, string filename, bool& found, vector<string> highlight);
	bool checkString(string input, string word);
	bool checkOnVector(vector<string> input, string word);
};

// OTHER FUNCTIONS
void lowerChar(char*& str);
void lowerString(string& str);
bool isDuplicate(vector<int> a, int b);
vector<int> mergeVector(vector<int> a, vector<int> b);
void fontSize(CONSOLE_FONT_INFOEX& cfi, int x, int y);

#endif  // !_FUNCTION_H_