#include "stdafx.h"

#include "tree.h"


using namespace std;


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

			if (p->left == nullptr)
			{
				*tmp = p->father->left;
			}
			else
			{
				*tmp = p;
			}

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
