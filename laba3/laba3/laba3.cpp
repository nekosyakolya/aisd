// laba3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

static const int ARGUMENTS_COUNT = 3;

using namespace std;

struct Node
{
	std::string name;
	Node *left;
	Node *right;
	Node *father;
	size_t level;
	bool isFile;
};


bool IsValidNumOfArguments(int argc)
{
	return (argc == ARGUMENTS_COUNT);
}


bool AreValidInputAndOutputFiles(char * argv[], ifstream &input, ofstream & output)
{
	if (!input.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return  false;
	}
	if (input.peek() == ifstream::traits_type::eof())
	{
		cout << "Empty file " << argv[1] << "\n";
		return false;
	}
	if (!output.is_open())
	{
		cout << "Failed to open " << argv[2] << " for writing" << "\n";
		return false;
	}
	return true;
}


void OutputToFile(Node *root, ostream & output)
{
	string result;
	if (root != nullptr)
	{
		result = "";
		for (size_t i = 1; i <= root->level; ++i)
		{
			result += ".";
		}
		if (root->isFile)
		{
			result += "*";
		}
		output << result << root->name << endl;
		OutputToFile(root->left, output);
		OutputToFile(root->right, output);
	}

}


void OutputData(Node *tmp)
{
	cout << "Элементы: " << endl;
	while (tmp != nullptr)
	{
		cout << tmp->name << endl;
		tmp = tmp->right;
	}
}


Node *Open(Node **tmp, bool & isIt)
{
	Node *newNode = new Node;
	newNode = *tmp;
	*tmp = (*tmp)->left;

	if (newNode->isFile)
	{
		cout << "Это файл" << endl;
		isIt = false;
	}
	else if (*tmp == nullptr)
	{
		cout << "Папка пуста" << endl;
		isIt = false;
	}
	else
	{
		newNode = *tmp;
	}
	return newNode;
}


Node *Search(Node ** tmp, bool & isIt)
{

	Node *newNode = new Node;
	newNode = *tmp;
	string name = "";
	cin >> name;
	while (*tmp != nullptr)
	{
		if ((*tmp)->name == name)
		{
			return *tmp;
		}
		
		*tmp = (*tmp)->right;
	}
	isIt = false;
	return newNode;
}


int main(int argc, char * argv[])
{
	setlocale(LC_ALL, "");
	if (!IsValidNumOfArguments(argc))
	{
		cout << "Invalid arguments count\n"
			<< "Usage: laba3.exe <input file> <output file>\n";
		return EXIT_FAILURE;
	}

	ifstream input(argv[1]);

	ofstream output(argv[2]);
	if (!AreValidInputAndOutputFiles(argv, input, output))
	{
		return EXIT_FAILURE;
	}


	Node *root = new Node;
	getline(input, root->name);
	root->level = 0;
	root->isFile = false;
	root->father = nullptr;
	root->left = nullptr;
	root->right = nullptr;

	size_t level = 0;

	size_t k;

	Node *tmp = new Node;
	tmp = root;
	string value;
	Node *p = new Node;

	while (getline(input, value))
	{

		k = 0;
		Node *newNode = new Node;

		for (size_t i = 0; value[i] == '.'; ++i)
		{
			++k;
		}
		newNode->isFile = false;
		if (value[k] == '*')
		{
			newNode->isFile = true;
			newNode->name = value.substr(k + 1);
		}
		else
		{
			newNode->name = value.substr(k);
		}
		
		newNode->left = nullptr;
		newNode->right = nullptr;
		newNode->level = k;

		if (k > level)
		{
			tmp->left = newNode;
			newNode->father = tmp;
		}
		else if (k == level)
		{
			tmp->right = newNode;
			newNode->father = tmp->father;
		}
		else
		{
			p = tmp;
			for (size_t i = 1; i <= (level - k); ++i)
			{
				p = p->father;
			}
			newNode->father = p->father;
			p->right = newNode;
		}
		level = k;
		tmp = newNode;
	}

	
	tmp = root;
	bool isIt = true;
	bool isOpen = true;

	string userAnswer;
	while (!cin.eof())
	{

		
		cout << "Вы находитесь в: ";
		if (isOpen && tmp->father != nullptr)
		{
			cout << tmp->father->name;
		}
		else
		{
			cout << tmp->name;
		}
		cout << endl;
		
		if (isOpen)
		{
			OutputData(tmp);
		}
		

		userAnswer = "";
		cout << "Введите 1 для открытия " << endl;
		cout << "Введите 2 для закрытия " << endl;
		cout << "Введите 4 чтобы переименовать текущий файл(папку)" << endl;
		cin >> userAnswer;
		if (userAnswer == "1")
		{
			if (tmp->right != nullptr && isOpen)
			{
				cout << "Введите имя файла или папки для открытия" << endl;
				tmp = Search(&tmp, isIt);
				if (!isIt)
				{
					cout << "Такой папки или файла нет в природе" << endl;
				}
			}
			isOpen = true;
			if (tmp != nullptr  && isIt)
			{
				tmp = Open(&tmp, isOpen);
			}

		}
		if (userAnswer == "2")
		{
			if (tmp->father == nullptr || (tmp->father->father == nullptr && tmp->left != nullptr))
			{
				tmp = root;
			}
			else if (tmp->left == nullptr && !isOpen)
			{
				tmp = tmp->father->left;
			}
			else
			{
				tmp = tmp->father->father->left;
			}

			isOpen = true;
		}
		if (userAnswer == "4")
		{
			string newName = "";
			cout << "Введите новое название" << endl;
			cin >> newName;
			if (tmp == root || !isOpen)
			{
				tmp->name = newName;
				
			}
			else if (tmp != nullptr)
			{
				tmp->father->name = newName;
			}
			cout << "Новое название: " << newName << endl;
		}
		isIt = true;
	}

	OutputToFile(root, output);  //пока в cout
	return 0;
}




