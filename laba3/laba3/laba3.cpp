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
	bool isLastSon;
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


void OutputToFile(Node *root)
{
	string result;
	if (root != nullptr)
	{
		result = "";
		for (size_t i = 1; i <= root->level; ++i)
		{
			result += ".";
		}
		cout << result << root->name << endl;
		OutputToFile(root->left);
		OutputToFile(root->right);
	}

}

int main(int argc, char * argv[])
{
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
	root->isLastSon = true;
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
		newNode->name = value.substr(k);
		
		newNode->left = nullptr;
		newNode->right = nullptr;
		newNode->level = k;

		if (k > level)
		{
			tmp->left = newNode;
			newNode->father = tmp;
			newNode->isLastSon = true;
		}
		else if (k == level)
		{
			tmp->right = newNode;
			newNode->father = tmp->father;
			tmp->isLastSon = false;
			newNode->isLastSon = true;
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
			p->isLastSon = false;
			newNode->isLastSon = true;
		}
		level = k;
		tmp = newNode;
	}
	OutputToFile(root);
	return 0;
}

