
//21. Информация  о  файлах  на  жестких  дисках   компьютера
//записана  с  помощью  дерева.Обеспечить выполнение следующих
//операций :
//1) загрузку дерева в память из файла;
//2) обход дерева папок в  режиме  диалога(раскрыиме папок,
//подъем на уровень и т.п.);
//3) корректировку  дерева при создании новых папок и файлов,
//их переименовании, копировании, переносе и удалении.
//4) сохранение дерева в файле(13).

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include "windows.h"
#include <conio.h>

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


void Delete(Node **root)
{
	
	if (*root != nullptr)
	{
		Delete(&(*root)->left);
		Delete(&(*root)->right);
		delete (*root);
		(*root)->right = nullptr;
		(*root)->left = nullptr;
		(*root)->father = nullptr;
		*root = nullptr;
	}

}

void RecalculationLevel(Node **root)
{

	if (*root != nullptr)
	{

		(*root)->level = (*root)->father->level + 1;
		RecalculationLevel(&(*root)->left);
		RecalculationLevel(&(*root)->right);
	}

}


void OutputData(Node *tmp)
{
	cout << "Элементы: " << endl;
	cout << "> ";
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



Node *Create(Node **tmp, const bool& isFile)
{
	string newName = "";
	cout << "Введите название" << endl;
	if (getline(cin, newName))
	{
		Node *newNode = new Node;
		newNode->name = newName;
		newNode->isFile = isFile;
		newNode->left = nullptr;
		newNode->right = nullptr;
		newNode->father = (*tmp)->father;

		newNode->level = (*tmp)->level;

		while ((*tmp)->right != nullptr)
		{
			*tmp = (*tmp)->right;
		}
		(*tmp)->right = newNode;
	}
	
	cin.clear();
	return (*tmp)->father->left;
}



//Node *CopyElement(Node **tmp, Node **father)
//{
//
//	if (*tmp == nullptr)
//	{
//		return nullptr;
//	}
//
//	Node *newNode = new Node;
//	Node *newFather = new Node;
//	newFather->father = (*father)->father;
//	newFather->name = (*father)->name;
//	newFather->level = (*father)->level;
//	newFather->isFile = (*father)->isFile;
//	newFather->left = (*father)->left;
//	newFather->right = (*father)->right;
//
//	newNode->father = newFather;
//	newNode->name = (*tmp)->name;
//	newNode->level = (*tmp)->level;
//	newNode->isFile = (*tmp)->isFile;
//
//	newNode->left = CopyElement(&(*tmp)->left, &newNode);
//	newNode->right = CopyElement(&(*tmp)->right, &newNode->father);
//	return newNode;
//}



Node *CopyElement(Node *tmp, Node *father)
{

	if (tmp == nullptr)
	{
		return nullptr;
	}

	Node *newNode = new Node;
	father->left = newNode;

	newNode->father = father;
	newNode->name = tmp->name;
	newNode->level = tmp->level;
	newNode->isFile = tmp->isFile;

	newNode->left = CopyElement(tmp->left, newNode);
	newNode->right = CopyElement(tmp->right, father);
	return newNode;
}



void AddNewElement(Node **tmp, bool &isOpen, const bool& isFile)
{
	if (!isOpen && (*tmp)->isFile)
	{

		cout << "Вы не можете добавить элемент в файл" << endl;
	}
	else if (!isOpen)
	{
		string newName = "";
		cout << "Введите название" << endl;
		if (getline(cin, newName))
		{
			Node *newNode = new Node;
			newNode->name = newName;
			newNode->isFile = isFile;
			newNode->left = nullptr;
			newNode->right = nullptr;
			newNode->father = *tmp;

			newNode->level = (*tmp)->level + 1;

			(*tmp)->left = newNode;
			*tmp = (*tmp)->left;
			isOpen = true;
		}
		cin.clear();

	}
	else
	{

		*tmp = Create(tmp, isFile);
	}

}


void ReadTree(Node **root, istream & input)
{
	getline(input, (*root)->name);
	(*root)->level = 0;
	(*root)->isFile = false;
	(*root)->father = nullptr;
	(*root)->left = nullptr;
	(*root)->right = nullptr;
	size_t level = 0;
	size_t k;
	Node *tmp = new Node;
	tmp = *root;
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
}


void OutputMenu()
{
	cout << "Нажмите Enter для открытия " << endl
	<< "Нажмите Esc для закрытия " << endl
	<< "Нажмите + для создания нового файла в текущей директории" << endl
	<< "Нажмите * для создания новой папки в текущей директории" << endl
	<< "Нажмите 1 чтобы переименовать текущий файл(папку)" << endl
	<< "Нажмите Delete чтобы удалить текущий файл(папку)" << endl
	<< "Нажмите Backspace чтобы переместить текущий файл(папку)" << endl
	<< "Нажмите Insert чтобы вставить файл(папку)в текущую директорию" << endl
	<< "Нажмите Tab чтобы скопировать текущий файл(папку)" << endl;
}


void OutputInfo(Node **tmp, const bool & isOpen)
{
	cout << "Вы находитесь в: ";
	if (isOpen && (*tmp)->father != nullptr)
	{
		cout << (*tmp)->father->name;
	}
	else
	{
		cout << (*tmp)->name;
	}
	cout << endl;
	if (isOpen)
	{
		OutputData(*tmp);
	}
}

void OpenData(Node **tmp, bool & isOpen, const bool & isIt)
{
	isOpen = true;
	if (tmp != nullptr  && isIt)
	{
		*tmp = Open(tmp, isOpen);
	}
}


void CloseData(Node **tmp, bool & isOpen, Node **root)
{
	if ((*tmp)->father == nullptr || ((*tmp)->father->father == nullptr && (*tmp)->left != nullptr))
	{
		*tmp = *root;
	}
	else if ((*tmp)->left == nullptr && !isOpen)
	{
		*tmp = (*tmp)->father->left;
	}
	else
	{
		*tmp = (*tmp)->father->father->left;
	}

	isOpen = true;
}



void DeleteThisElement(Node **tmp, bool & isOpen)
{
	Node *p = new Node;
	if (!isOpen)
	{
		if ((*tmp)->father->left == *tmp)
		{
			(*tmp)->father->left = (*tmp)->right;

			p = ((*tmp)->right == nullptr) ? (*tmp)->father : (*tmp)->right;

			delete (*tmp);
			(*tmp)->left = nullptr;
			(*tmp)->right = nullptr;
			(*tmp)->father = nullptr;

			*tmp = p;
		}
		else
		{
			//не первый элемент

			p = *tmp;
			*tmp = (*tmp)->father->left;
			while ((*tmp)->right != p)
			{
				*tmp = (*tmp)->right;
			}
			(*tmp)->right = (*tmp)->right->right;

			delete (p);

			p->right = nullptr;
			p->father = nullptr;
			p->left = nullptr;

			*tmp = ((*tmp)->father->left == nullptr) ? (*tmp)->father : (*tmp)->father->left;
		}

	}
	else
	{

		if ((*tmp)->father == (*tmp)->father->father->left)
		{

			// это если папка не пуста
			*tmp = (*tmp)->father;
			Delete(&(*tmp)->left);

			(*tmp)->father->left = (*tmp)->right;
			p = ((*tmp)->right == nullptr) ? (*tmp)->father : (*tmp)->right;

			delete (*tmp);
			(*tmp)->right = nullptr;
			(*tmp)->father = nullptr;
			(*tmp)->left = nullptr;

			*tmp = p;
		}
		else
		{
			//не первый элемент
			// это если папка не пуста

			*tmp = (*tmp)->father;
			Delete(&(*tmp)->left);

			p = *tmp;


			*tmp = (*tmp)->father->left;
			while ((*tmp)->right != p)
			{
				*tmp = (*tmp)->right;
			}
			(*tmp)->right = (*tmp)->right->right;

			delete (p);

			p->right = nullptr;
			p->father = nullptr;
			p->left = nullptr;
			*tmp = ((*tmp)->father->left == nullptr) ? (*tmp)->father : (*tmp)->father->left;

		}
	}
	isOpen = true;
}



void RenameElement(Node **tmp, Node **root, bool & isOpen)
{
	string newName = "";
	cout << "Введите новое название" << endl;
	if (getline(cin, newName))
	{
		if (*tmp == *root || !isOpen)
		{
			(*tmp)->name = newName;

		}
		else if (tmp != nullptr)
		{
			(*tmp)->father->name = newName;
		}
		cout << "Новое название: " << newName << endl;
	}
	cin.clear();
	
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
	
	ReadTree(&root, input);

	Node *node = new Node;
	Node *p = new Node;
	Node *tmp = new Node;

	node = nullptr;
	tmp = root;
	bool isIt = true;
	bool isOpen = true;
	bool isBegin = true;

	int userAnswer;
	do
	{


		if (isBegin)
		{
			p = tmp;
			if (p->father != nullptr && isOpen)
			{
				p = p->father->left;
			}
			OutputInfo(&p, isOpen);
			cout << "Нажмите End для выхода из программы" << endl;
			cout << "Нажмите пробел для справки" << endl << endl;
		}

		

		userAnswer = _getch();
		switch (userAnswer)
		{
		case 13:
			OpenData(&tmp, isOpen, isIt);
			isBegin = true;
			break;
		case 27:
			CloseData(&tmp, isOpen, &root);
			isBegin = true;
			break;
		case 32:
			OutputMenu();
			break;
		case 43:
			AddNewElement(&tmp, isOpen, true);
			isBegin = true;
			break;
		case 42://*
			AddNewElement(&tmp, isOpen, false);
			isBegin = true;
			break;
		case 83:
			if (tmp == root || (tmp->father == root && isOpen))
			{
				Delete(&root);
				root = nullptr;
				cout << "Вы удалили корень" << endl;
			}
			else
			{
				DeleteThisElement(&tmp, isOpen);
			}
			isBegin = true;
			break;
		case 49://1
			RenameElement(&tmp, &root, isOpen);
			isBegin = true;
			break;
		case 8://переместиь backspace
			if (tmp == root || (tmp->father == root && isOpen))
			{
				cout << "Нельзя переместить корень" << endl;
			}
			else if (!isOpen)
			{
				node = tmp;
				if (tmp->father->left == tmp)
				{
					tmp->father->left = tmp->right;

					p = (tmp->right == nullptr) ? tmp->father : tmp->right;
					tmp = p;
				}
				else
				{
					p = tmp;

					tmp = tmp->father->left;
					while (tmp->right != p)
					{
						tmp = tmp->right;
					}

					tmp->right = tmp->right->right;

					tmp = (tmp->father->left == nullptr) ? tmp->father : tmp->father->left;
				}

			}
			else
			{

				node = tmp->father;
				if (tmp->father == tmp->father->father->left)
				{

					// это если папка не пуста
					tmp = tmp->father;

					tmp->father->left = tmp->right;
					p = (tmp->right == nullptr) ? tmp->father : tmp->right;

					tmp = p;
				}
				else
				{
					//не первый элемент
					// это если папка не пуста

					tmp = tmp->father;

					p = tmp;


					tmp = tmp->father->left;
					while (tmp->right != p)
					{
						tmp = tmp->right;
					}

					tmp->right = tmp->right->right;

					tmp = (tmp->father->left == nullptr) ? tmp->father : tmp->father->left;

				}
			}
			isOpen = true;
			isBegin = true;
			break;
		case 82://вставить insert
			if (node != nullptr)
			{
				if (!isOpen && tmp->isFile)
				{

					cout << "Вы не можете добавить элемент в файл" << endl;
				}

				else if (!isOpen)
				{
					tmp->left = node;
					node->father = tmp;
					node->right = nullptr;
					node->level = tmp->level + 1;
					p = tmp->left;
					RecalculationLevel(&p);
					tmp = node;

				}
				else
				{
					while (tmp->right != nullptr)
					{
						tmp = (tmp)->right;
					}
					tmp->right = node;

					node->father = tmp->father;
					node->right = nullptr;

					p = node;
					RecalculationLevel(&p);
					tmp = tmp->father->left;
				}
				isOpen = true;
				isBegin = true;
			}
			break;
		case 9://copy tab
			p = tmp;
			if (tmp == root || (tmp->father == root && isOpen))
			{

				Node *father = new Node;
				father->father = nullptr;
				father->left = nullptr;
				father->right = nullptr;
				father->isFile = false;
				father->level = 0;
				father->name = "";
				node = CopyElement(root, father);
			}
			else if (!isOpen)
			{

				Node *father = new Node;
				father->father = nullptr;
				father->left = nullptr;
				father->right = nullptr;
				father->isFile = false;
				father->level = 0;
				father->name = "";
				node = CopyElement(tmp, father);
				tmp = tmp->father->left;
			}
			else
			{

				Node *father = new Node;
				father->father = nullptr;
				father->left = nullptr;
				father->right = nullptr;
				father->isFile = false;
				father->level = 0;
				father->name = "";
				node = CopyElement(tmp->father, father);
			}
			tmp = p;
			//isOpen = true;
			isBegin = true;
			break;
		case 80:
			if (tmp->right != nullptr)
			{
				cout << "Вы находитесь в: ";
				if (tmp->father != nullptr)
				{
					cout << tmp->father->name << endl;
				}
				cout << "Элементы: " << endl;

				p = tmp->father->left;
				while (p != nullptr)
				{
					if (p == tmp->right)
					{
						cout << "> ";
					}

					cout << p->name << endl;
					p = p->right;
				}
				tmp = tmp->right;
				if (tmp->left == nullptr)
				{
					isOpen = false;
				}
				isBegin = false;
			}
			break;
		case 72:
			if (tmp != tmp->father->left)
			{
				cout << "Вы находитесь в: ";
				if (tmp->father != nullptr)
				{
					cout << tmp->father->name << endl;
				}
				cout << "Элементы: " << endl;
				p = tmp->father->left;
				while (p != nullptr)
				{
					if (p->right == tmp)
					{
						cout << "> ";
						tmp = p;
					}

					cout << p->name << endl;
					p = p->right;
				}
				if (tmp->left == nullptr)
				{
					isOpen = false;
				}
				isBegin = false;
			}
			break;
		default:
			break;
		}
	}while (userAnswer != 79 && root != nullptr);



	

	OutputToFile(root, output);
	return EXIT_SUCCESS;
}




