#include "function.h"

Node* Trie::createNode()
{
	Node* node = new Node;
	node->isLeaf = false;
	return node;
}

void Trie::insert(Node*& root, string str, int i)
{
	if (root == NULL)
		root = createNode();
	lowerString(str);
	Node* cur = root;
	int k = 0;
	while (k < str.size())
	{
		char x = str[k];
		if (x == '—') x == '-';
		if (x == '“') x = '"';
		if (x == '”') x = '"';
		if (x == '’') x = '\'';
		if (x == '‘') x = '\'';
		if (cur->mapkey.find(x) == cur->mapkey.end())
			cur->mapkey[x] = createNode();
		cur = cur->mapkey[x];
		k++;
	}
	if (cur->myv.empty())
		cur->myv.push_back(i);
	if ((!cur->myv.empty()) && i > cur->myv.back())
		cur->myv.push_back(i);
	cur->isLeaf = true;
}

void Trie::readStop(string ptr, Node*& root, int i)
{
	fstream file;
	file.open(ptr); string word;
	while (file >> word)
		insert(root, word, i);
	file.close();
}

void Trie::readWord(vector<string>& ptr, Node*& root, int i)
{
	vector<string> name;
	fstream file, file1;
	file.open(ptr.at(0));
	file1.open(ptr.at(1));
	string word, word1;
	while (file >> word && file1 >> word1) // take word and print
	{
		if (word.back() == ',' || word.back() == '.' || word.back() == ':' || word.back() == '?' || word.back() == '\"')
			word.pop_back();	
		insert(root, word, i);							
		if (word1.back() == ',' || word1.back() == '.' || word1.back() == ':' || word1.back() == '?' || word1.back() == '\"')
			word1.pop_back();			
		insert(root, word1, i + 1);
	}

	ptr.clear();
	file.close();
	file1.close();
}

void Trie::getFileName(Node*& root, char* str, vector<string>& vt)
{
	int i = 0;
	string titleName;
	vector<string> multi;
	for (auto& p : directory_iterator("data")) // data files put in folder "data"
	{
		titleName = p.path().filename().string();
		vt.push_back(titleName);
	}
	for (int j = 0; j < vt.size(); j++)
	{
		multi.push_back("data/" + vt.at(j));
		if (multi.size() == 2)
		{
			readWord(multi, root, i);
			i = i + 2;
		}
		else if (multi.size() != 2 && vt.size() - j < 2)
			readStop(multi.at(0), root, i);
	}
}

void Trie::deleteTrie(Node*& root)
{
	unordered_map<char, Node*>::iterator it;
	if (root == NULL)
		return;
	for (it = root->mapkey.begin(); it != root->mapkey.end(); it++)
		deleteTrie(it->second);
	delete root;
	root = NULL;
}

void Trie::removeStopWord(vector<string>& store, Node* root2)
{
	vector<string> result;
	checkPlus(store, root2, result);
	char* str3 = new char[50];
	for (int i = 0; i < store.size(); ++i)
	{
		str3 = new char[store.at(i).size() + 1];
		strcpy(str3, store.at(i).c_str());
		Node* key1 = getFile(root2, str3);
		if (key1 != NULL && key1->isLeaf != 0)
		{
			if (!checkOnVector(result, store.at(i)))
			{
				store.erase(store.begin() + i);
				--i;
			}
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

// find commonvector
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

// check if the input word is on the vector
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

bool Trie::checkString(string input, string word)
{
	int count = 0;
	lowerString(word);
	for (int i = 0; i < input.size(); i++)
		if (word.size() >= input.size() && input[i] == word[i])
			count++;
	if (word.size() > count)
		if (word[count] != '!' && word[count] != '?' && word[count] != '\''
			&& word[count] != '.' && word[count] != ',' && word[count] != ':')
			return false;
	if (count == input.size())
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

bool Trie::queryHastag(vector<string> input)
{
	for (int i = 0; i < input.size(); ++i)
	{
		if (input.at(i)[0] == '#')
			return true;
	}
	return false;
}

bool Trie::queryIntitle(string input)
{
	if (input.length() >= 8)
	{
		string temp = "";
		for (int i = 0; i < 8; ++i)
			temp += input[i];
		if (temp == "intitle:")
			return true;
	}
	return false;
}

bool Trie::queryFileType(string input)
{
	if (input.length() >= 9)
	{
		string temp = "";
		for (int i = 0; i < 9; ++i)
			temp += input[i];
		if (temp == "filetype:")
			return true;
	}
	return false;
}

bool Trie::queryExact(vector<string> input)
{
	string last = input.at(input.size() - 1);
	if (input.at(0)[0] == '\"' && last[last.size() - 1] == '\"')
		return true;
	else
		return false;
}

bool Trie::queryRange(vector<string>& input, string& start, string& end, string& sim)
{
	int count = 0;
	for (int i = 0; i < input.size(); i++)
	{
		size_t found = input.at(i).find("..");
		if (found != string::npos)
		{
			start = input.at(i).substr(0, found);
			end = input.at(i).substr(found + 2, input.at(i).size() - 1);
			input.erase(input.begin() + i);
			count++;
		}
	}
	if (count == 0)
		return false;
	int k = 0;
	string symbol = "", symbol2 = "";
	while (!isdigit(start[0]))
	{
		symbol = symbol + start[0];
		start.erase(start.begin());
	}
	while (!isdigit(end[0]))
	{
		symbol2 = symbol2 + end[0];
		end.erase(end.begin());
	}
	if (symbol == symbol2)
	{
		sim = symbol;
		return true;
	}
	else
		return false;
}

bool Trie::queryMinus(vector<string>& input, vector<string>& minus)
{
	int count = 0;
	for (int i = 0; i < input.size(); i++)
	{
		if (input.at(i)[0] == '-')
		{
			count++;
			input.at(i).erase(input.at(i).begin());
			minus.push_back(input.at(i));
			input.erase(input.begin() + i);
		}
	}
	if (count != 0)
		return true;
	else
		return false;
}

bool Trie::checkIntOnVector(vector<int>minus, int input)
{
	int count = 0;
	for (int i = 0; i < minus.size(); i++)
		if (minus.at(i) == input)
			count++;
	if (count != 0)
		return true;
	else
		return false;
}

void Trie::checkPlus(vector<string>& input, Node* root2, vector<string>& result)
{
	char* str2;
	for (int i = 0; i < input.size(); ++i)
	{
		if (input.at(i)[0] == '+')
		{
			input.at(i).erase(0, 1);
			str2 = new char[input.at(i).size() + 1];
			for (int j = 0; j < input.at(i).size() + 1; j++)
				str2[j] = input.at(i)[j];
			if (getFile(root2, str2) != NULL)
				result.push_back(str2);
			delete[] str2;
		}
	}
}

// excute every query
void Trie::QueryOperator(Node* root, char* str, vector<string>& vt, Node* root2)
{
	string word, input = str, start = "", end = "", sim;
	vector<int> common;
	vector<string> store, minus;
	stringstream iss(str);
	char* str2 = new char[20];
	int countN = 0, queryType, count;
	bool qAND = false, qOR = false, qPrice = false, qHastag = false,
		qIntitle = false, qExact = false, qMinus = false;
	clock_t start1;
	// QUERY FILETYPE
	if (queryFileType(input))
	{
		cout << "QUERY FILETYPE" << endl << endl;
		fstream res;
		string type = "";
		int count = 0, j = 0, check = 0;
		for (int i = 9; i < input.length(); ++i)
			type += input[i];
		if (type[0] == ' ')
			type.erase(0, 1);
		if (type.empty())
		{
			cout << "Error!!! Please type in a type of file." << endl;
			return;
		}
		clock_t start1 = clock();
		for (int i = 0; i < vt.size(); ++i)
		{
			for (int k = vt.at(i).length() - type.length(); k < vt.at(i).length(); ++k)
			{
				if (vt.at(i)[k] == type[j++])
					++count;
			}
			j = 0;
			if (count == type.length())
			{
				++check;
				res.open("data/" + vt.at(i), ios::in);
				if (!res.is_open())
					--check;
				// cout << "Can not load file." << endl << endl;
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 138);
					cout << "***" << vt.at(i) << ":";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
					cout << endl << endl;
					string data, ww;
					stringstream getdata(data);
					while (getdata >> ww)
					{
						for (int k = 0; k <= ww.size(); k++)
						{
							if (ww[k] == '—') ww[k] == '-';
							if (ww[k] == '“') ww[k] = '"';
							if (ww[k] == '”') ww[k] = '"';
							if (ww[k] == '’') ww[k] = '\'';
							if (ww[k] == '‘') ww[k] = '\'';
						}
					}
					getline(res, data, '.');
					cout << data << "..." << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
					cout << endl << "======================================"
						<< "==============================================="
						<< "==============================================="
						<< endl << endl;
				}
				res.close();
			}
			count = 0;
			if (check >= 10)
				break;
		}
		if (check == 0)
			cout << "Error!!! Can not find this filetype." << endl << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout << "=> Running time: " << (double)(clock() - start1) / CLOCKS_PER_SEC << endl;
		return;
	}
	while (iss >> word)
	{
		lowerString(word);
		store.push_back(word);
	}
	// QUERY INTITLE
	if (queryIntitle(store.at(0)))
	{
		queryType = 5;
		if (store.at(0).length() > 8)
			store.at(0).erase(0, 8);
		else /*store.at(0).length() == 8*/
		{
			if (store.size() == 1)
			{
				cout << "QUERY INTITLE" << endl << endl
					<< "Error!!! Please type in a keyword." << endl << endl;
				return;
			}
			else
				store.erase(store.begin());
		}
		getQueryAnd(root2, store, str2, common, countN, queryType);
	}
	// QUERY EXACT
	else if (queryExact(store))
	{
		store.at(0).erase(store.at(0).begin());
		store.at(store.size() - 1).pop_back();;
		queryType = 6;
		getQueryAnd(root2, store, str2, common, countN, queryType);
	}
	// QUERY RANGE
	else if (queryRange(store, start, end, sim))
	{
		start1 = clock();
		if (!store.empty()) store.push_back("demo");
		for (int i = atoi(start.c_str()); i <= atoi(end.c_str()); i++)
		{
			countN = 0;
			common.clear();
			if (!store.empty())
				store.pop_back();
			store.push_back(sim + to_string(i));
			queryType = 6;
			getQueryAnd(root2, store, str2, common, countN, queryType);
			count = 0;
			for (int j = 0; j < common.size(); j++)
			{
				if (count < 1)
					if (countN == store.size())
						outPutResult("data/" + vt.at(common.at(j)), store, count, false, false);
					else
						break;
			}
		}
		cout << "=> Running time: " << (double)(clock() - start1) / CLOCKS_PER_SEC << endl;
		goto b;
	}
	// QUERY OR
	else if (checkOnVector(store, "or"))
	{
		getQueryOr(root2, store, str2, common, countN);
		queryType = 2;
	}
	// QUERY MINUS
	else if (queryMinus(store, minus))
	{
		queryType = 7;
		getQueryAnd(root2, store, str2, common, countN, queryType);
		str2 = new char[20];
		vector<int> common2;
		getQueryOr(root2, minus, str2, common2, countN);
		for (int i = 0; i < common.size(); i++) {
			if (checkIntOnVector(common2, common.at(i)))
			{
				common.erase(common.begin() + i);
				i--;
			}
		}
	}
	// QUERY PRICE
	else if (queryPrice(store))
	{
		queryType = 3;
		getQueryAnd(root2, store, str2, common, countN, queryType);
	}
	// QUERY HASTAG
	else if (queryHastag(store))
	{
		queryType = 4;
		getQueryAnd(root2, store, str2, common, countN, queryType);
	}
	// QUERY AND
	else
	{
		queryType = 1;
		getQueryAnd(root2, store, str2, common, countN, queryType);
	}
	count = 0;
	cout << endl;
	start1 = clock();
	for (int i = 0; i < common.size(); i++)
	{
		if (count < 10)
		{
			// Output for query and
			if (queryType == 1)
			{
				if (!qAND)
				{
					cout << "QUERY AND" << endl << endl;
					qAND = true;
				}
				if (countN == store.size())
					outPutResult("data/" + vt.at(common.at(i)), store, count, false, false);
				else
					goto a;
			}
			// Output for query or
			else if (queryType == 2)
			{
				if (!qOR)
				{
					cout << "QUERY OR" << endl << endl;
					qOR = true;
				}
				outPutResult("data/" + vt.at(common.at(i)), store, count, false, false);
			}
			// Output for query price
			else if (queryType == 3)
			{
				if (!qPrice)
				{
					cout << "QUERY PRICE" << endl << endl;
					qPrice = true;
				}
				outPutResult("data/" + vt.at(common.at(i)), store, count, false, false);
			}
			// Output for query hastag
			else if (queryType == 4)
			{
				if (!qHastag)
				{
					cout << "QUERY HASTAG" << endl << endl;
					qHastag = true;
				}
				outPutResult("data/" + vt.at(common.at(i)), store, count, false, false);
			}
			// Output for query intitle
			else if (queryType == 5)
			{
				if (!qIntitle)
				{
					cout << "QUERY INTITLE" << endl << endl;
					qIntitle = true;
				}
				if (countN == store.size())
					outPutResult("data/" + vt.at(common.at(i)), store, count, false, true);
				else
					goto a;
			}
			// Output for query exact
			else if (queryType == 6)
			{
				if (!qExact)
				{
					cout << "QUERY EXACT" << endl << endl;
					qExact = true;
				}
				if (countN == store.size())
					outPutResult("data/" + vt.at(common.at(i)), store, count, true, false);
			}
			// Output for query minus
			else if (queryType == 7)
			{
				if (!qMinus)
				{
					cout << "QUERY MINUS" << endl << endl;
					qMinus = true;
				}
				if (countN == store.size())
					outPutResult("data/" + vt.at(common.at(i)), store, count, false, false);
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		}
		else
			break;
	}
a:
	cout << "=> Running time: " << (double)(clock() - start1) / CLOCKS_PER_SEC << endl;
b:
	delete[] str2;
}

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