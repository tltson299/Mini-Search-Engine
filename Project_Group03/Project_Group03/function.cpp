#include "function.h"

Node* Trie::createNode()
{
	Node* node = new Node;
	node->isLeaf = false;
	return node;
}

void Trie::insert(Node*& root, char* str, int i)
{
	if (root == NULL)
		root = createNode();
	lowerChar(str);
	Node* cur = root;
	while (*str)
	{
		lowerChar(str);
		if (cur->mapkey.find(*str) == cur->mapkey.end())
			cur->mapkey[*str] = createNode();
		cur = cur->mapkey[*str];
		str++;
	}
	if (cur->myv.empty())
		cur->myv.push_back(i);
	if ((!cur->myv.empty()) && i > cur->myv.back())
		cur->myv.push_back(i);
	cur->isLeaf = true;
}

void Trie::readWord(string ptr, Node*& root, char* str, int i)
{
	fstream file;
	string word;
	file.open(ptr);
	while (file >> word) // take word and print
	{
		str = new char[word.size() + 1];
		for (int i = 0; i < word.size() + 1; i++)
			str[i] = word[i];
		insert(root, str, i);
	}
	file.close();
}

void Trie::deleteTrie(Node*& root)
{
	map<char, Node*>::iterator it;
	if (root == NULL)
		return;
	for (it = root->mapkey.begin(); it != root->mapkey.end(); it++)
		deleteTrie(it->second);
	delete root;
}

void Trie::getFileName(Node*& root, char* str, vector<string>& vt)
{
	fstream fo;
	int i = 0;
	string titleName;
	fo.open("file_name.txt", ios::out);
	for (auto& p : directory_iterator("data")) // data files put in folder "data"
	{
		fo << p.path().filename() << "\n"; // p.path(): file name
		titleName = p.path().filename().string();
		vt.push_back(titleName);
		readWord("data/" + titleName, root, str, i);
		i++;
	}
	fo.close();
}

// remove stopwords
void Trie::removeStopWord(vector<string>& store, Node* root2)
{
	char* str3 = new char[50];
	for (int i = 0; i < store.size(); ++i)
	{
		str3 = new char[store.at(i).size() + 1];
		strcpy(str3, store.at(i).c_str());
		Node* key1 = getFile(root2, str3);
		if (key1 != NULL && key1->isLeaf != 0)
		{
			store.erase(store.begin() + i);
			--i;
		}
		delete[] str3;
	}
}

// similar to search function but this function also get the leaf node
Node* Trie::getFile(Node* root, char* str)
{
	lowerChar(str);
	if (root == NULL)
		return NULL;
	Node* cur = root;
	while (*str)
	{
		cur = cur->mapkey[*str];
		if (cur == NULL)
			return NULL;
		str++;
	}
	return cur;
}

void Trie::commonVector(vector<int> inputvt, vector<int>& common)
{
	int i = 0, j = 0;
	vector<int> vec;
	while (i < inputvt.size() && j < common.size())
	{
		if (inputvt.at(i) < common.at(j))
			i++;
		else if (common.at(j) < inputvt.at(i))
			j++;
		else /* if arr1[i] == arr2[j] */
		{
			vec.push_back(common.at(j));
			i++;
			j++;
		}
	}
	common = vec;
}

bool Trie::checkString(string input, string word)
{
	int count = 0;
	lowerString(word);
	for (int i = 0; i < input.size(); i++)
		if (word.size() >= input.size() && input[i] == word[i])
			count++;
	if (word.size() >= count + 1)
		if (word[count + 1] != '!' || word[count + 1] != '?' ||
			word[count + 1] != '\'' || word[count + 1] != '.' || word[count + 1] != ',')
			return false;
	if (count == input.size())
		return true;
	else
		return false;
}

// output the sentence that contain keywords
void Trie::ouputVector(vector<string> mys, string filename, bool& found, vector<string> highlight)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	if (!found)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 138);
		cout << "***";
		for (int i = 5; i < filename.length(); ++i)
			cout << filename[i];
		cout << ":";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		cout << endl << endl;
	}
	for (int i = 0; i < mys.size(); i++)
	{
		if (!checkOnVector(highlight, mys.at(i)))
			cout << mys.at(i) << " ";
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 138); // highlight keywords
			cout << mys.at(i);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); // stop highlight
			cout << " ";
		}
	}
	cout << endl;
}
void Trie::ouputVectorEx(vector<string> mys, string filename, bool& found, vector<string> highlight, int pos)
{
	int dis;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	if (!found)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 138);
		cout << "***";
		for (int i = 5; i < filename.length(); ++i)
			cout << filename[i];
		cout << ":";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		cout << endl << endl;
	}
	for (int i = 0; i < mys.size(); i++)
	{
		if (!checkOnVector(highlight, mys.at(i)))
			cout << mys.at(i) << " ";
		else if (checkOnVector(highlight, mys.at(i)) && i >= pos - highlight.size() - 1 && i <= pos)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 138); // highlight keywords
			cout << mys.at(i);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); // stop highlight
			cout << " ";
		}
		else
			cout << mys.at(i) << " ";
	}
	cout << endl;
}
// check if keywords are on the sentence
bool Trie::checkOnVector(vector<string> input, string word)
{
	int count = 0;
	for (int i = 0; i < input.size(); i++)
		if (checkString(input.at(i), word))
			count++;
	if (count != 0)
		return true;
	else
		return false;
}

void Trie::outPutResult(string fileName, vector<string> input, int& count, bool exact, bool intitle)
{
	fstream file;
	string word;
	vector<string> mys;
	bool found = false;
	file.open(fileName);
	while (file >> word) //take word and print
	{
		for (int i = 0; i < word.size() + 1; i++) {
			if (word[i] == '—') word[i] == '-';
			if (word[i] == '“') word[i] = '"';
			if (word[i] == '”') word[i] = '"';
			if (word[i] == '’') word[i] = '\'';
			if (word[i] == '‘') word[i] = '\'';
		}
		mys.push_back(word);
		if (word[word.size() - 1] == '.' || (word.size() > 1 && word[word.size() - 2] == '.'))
		{
			int check = 0, remark;
			string oldone = " ";
			for (int i = 0; i < mys.size(); i++)
			{
				if (mys.at(i) != oldone && checkOnVector(input, mys.at(i)))
				{
					oldone = mys.at(i);
					check++;
				}
			}
			if (check != 0)
			{
				if (exact == true && check >= input.size())
				{
					int examine = 0;
					for (int i = 0; i < mys.size(); i++)
					{
						int k = i; int count = 0;
						for (int j = 0; j < input.size(); j++)
						{
							if (k < mys.size())
							{
								string cmpr = mys.at(k); lowerString(cmpr);
								if (cmpr == input.at(j)) {
									count++;
									if (count == input.size())
										remark = k;
								}
								k++;
							}
						}
						if (count == input.size()) examine++;
					}
					if (examine != 0)
					{
						ouputVectorEx(mys, fileName, found, input, remark);
						found = true;
					}
				}
				else if (exact == false)
				{
					ouputVector(mys, fileName, found, input);
					found = true;
				}
			}
			mys.clear();
			if (intitle)
				break;
		}
	}
	if (found)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout << endl << "======================================"
			<< "==============================================="
			<< "==============================================="
			<< endl << endl;
		++count;
	}
	file.close();
}

void Trie::getQueryAnd(Node* root2, vector<string>& store, char*& str2, vector<int>& common, int& countN, int qt)
{
	if (qt != 6)
		removeStopWord(store, root2);
	for (int i = 0; i < store.size(); i++)
	{
		if (store.empty())
			break;
		str2 = new char[store.at(i).size() + 1];
		for (int j = 0; j < store.at(i).size() + 1; j++)
			str2[j] = store.at(i)[j];
		Node* key = getFile(root, str2);
		if (key != NULL && key->isLeaf != 0)
		{
			if (common.empty())
				common = key->myv;
			else
				commonVector(key->myv, common);
			countN++;
		}
	}
}

void Trie::getQueryOr(Node* root2, vector<string>& store, char*& str2, vector<int>& common, int& countN)
{
	removeStopWord(store, root2);
	for (int i = 0; i < store.size(); i++)
	{
		if (store.empty())
			break;
		str2 = new char[store.at(i).size() + 1];
		for (int j = 0; j < store.at(i).size() + 1; j++)
			str2[j] = store.at(i)[j];
		Node* key = getFile(root, str2);
		if (key != NULL && key->isLeaf != 0)
		{
			if (common.empty())
				common = key->myv;
			else
				common = mergeVector(key->myv, common);
		}
	}
}
bool Trie::queryPrice(vector<string> input)
{
	for (int i = 0; i < input.size(); ++i)
	{
		if (input.at(i)[0] == '$')
			return true;
	}
	return false;
}


// OTHER FUNCTIONS
void title()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "     oooooo  ooooooo       oo       oooooooo    oooooooo  oo     oo        ooooooo  ooo     oo   oooooooo    oo  ooo     oo  ooooooo" << endl
		<< "    oo       oo	          oooo      oo    ooo  oo         oo     oo        oo       oooo    oo  oo           oo  oooo    oo  oo  " << endl
		<< "    oo       oo          oo  oo     oo   ooo   oo         oo     oo        oo       oo oo   oo  oo           oo  oo oo   oo  oo     " << endl
		<< "      ooo    ooooooo    oooooooo    oooooo     oo         ooooooooo        ooooooo  oo  oo  oo  oo     oooo  oo  oo  oo  oo  ooooooo" << endl
		<< "         oo  oo        oo      oo   oo ooo     oo         oo     oo        oo       oo   oo oo  oo      oo   oo  oo   oo oo  oo     " << endl
		<< "         oo  oo       oo        oo  oo   ooo   oo         oo     oo        oo       oo    oooo  oo      oo   oo  oo    oooo  oo     " << endl
		<< "    oooooo   ooooooo oo          oo oo     ooo  oooooooo  oo     oo        ooooooo  oo     ooo    ooooooo    oo  oo     ooo  ooooooo" << endl
		<< endl
		<< "\t\t\t\t\t\t\tGROUP 3 - 19CTT2 - HCMUS"
		<< endl << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
}

void lowerChar(char*& str)
{
	int n = strlen(str);
	for (int i = 0; i < n; ++i)
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += ('a' - 'A');
}

void lowerString(string& str)
{
	int n = str.length();
	for (int i = 0; i < n; ++i)
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += ('a' - 'A');
}

// merge 2 vector
bool isDuplicate(vector<int> a, int b)
{
	for (int i = 0; i < a.size(); ++i)
		if (b == a.at(i))
			return true;
	return false;
}

vector<int> mergeVector(vector<int> a, vector<int> b)
{
	for (int i = 0; i < b.size(); ++i)
	{
		if (!isDuplicate(a, b.at(i)))
			a.push_back(b.at(i));
	}
	return a;
}

void fontSize(CONSOLE_FONT_INFOEX& cfi, int x, int y)
{
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = x; // width of each character in the font
	cfi.dwFontSize.Y = y; // height of each character in the font
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // choose font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}