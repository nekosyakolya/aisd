#include "stdafx.h"
#include <iostream>

#include "tree.h"

std::fstream file("sort.dat", std::ios::binary | std::ios::in);

void DisposeTree(Node **root)
{
	if (*root != nullptr)
	{
		DisposeTree(&(*root)->left);
		DisposeTree(&(*root)->right);
		delete (*root);
		(*root)->right = nullptr;
		(*root)->left = nullptr;
		*root = nullptr;
	}
}



void Insert(Node **ptr, const Info &data, size_t & num)
{
	if (*ptr == nullptr)
	{
		*ptr = new Node;
		(*ptr)->left = nullptr;
		(*ptr)->right = nullptr;
		(*ptr)->data.key = data.key;
		(*ptr)->data.value = data.value;
		(*ptr)->insertedInRightPlace = false;
		++num;
	}
	else if ((*ptr)->data.key > data.key)
	{
		Insert(&(*ptr)->left, data, num);
	}
	else
	{
		Insert(&(*ptr)->right, data, num);
	}
}


void CopyTreeToFile(Node **ptr)
{
	if (*ptr != nullptr)
	{
		CopyTreeToFile(&(*ptr)->left);
		file << (*ptr)->data.key;
		file << " ";
		file << (*ptr)->data.value;
		CopyTreeToFile(&(*ptr)->right);
	}
}


void MergeTreeFile(Node **ptr, bool &doReadNextWord, std::fstream & tmp, Info & data)
{
	if ((*ptr)->left != nullptr)
	{
		MergeTreeFile(&(*ptr)->left, doReadNextWord, tmp, data);
	}
	if (!file.eof() && doReadNextWord)
	{
		file >> data.key;
		file >> data.value;
	}

	while (!file.eof() && data.key <= (*ptr)->data.key)
	{
		//пишем
		tmp << data.key;
		tmp << " ";
		tmp << data.value;
		//читаем
		file >> data.key;
		file >> data.value;
	}

	if (file.eof())
	{
		doReadNextWord = false;
	}
	//вынести в фию
	if (data.key < (*ptr)->data.key && !file.eof())
	{
		tmp << data.key;
		tmp << " ";
		tmp << data.value;
		doReadNextWord = true;
	}
	else if (data.key > (*ptr)->data.key && !file.eof())
	{
		tmp << (*ptr)->data.key;
		tmp << " ";
		tmp << (*ptr)->data.value;
		doReadNextWord = false;
		(*ptr)->insertedInRightPlace = true;
	}
	else if (data.key == (*ptr)->data.key && !file.eof())
	{
		tmp << data.key;
		tmp << " ";
		tmp << data.value;
		doReadNextWord = true;
		//(*ptr)->insertedInRightPlace = true;//у нас не выпишется это слово еще раз из дерева
	}

	if ((*ptr)->right != nullptr)
	{
		MergeTreeFile(&(*ptr)->right, doReadNextWord, tmp, data);
	}
}



void CopyNotSortedTreeToFile(Node **ptr, std::fstream & tmp)
{
	if ((*ptr)->left != nullptr)
	{
		CopyNotSortedTreeToFile(&(*ptr)->left, tmp);
	}

	if (!(*ptr)->insertedInRightPlace)
	{
		tmp << (*ptr)->data.key;
		tmp << " ";
		tmp << (*ptr)->data.value;
	}

	if ((*ptr)->right != nullptr)
	{
		CopyNotSortedTreeToFile(&(*ptr)->right, tmp);
	}

}

void CopyDataFile(std::fstream & tmp)
{
	file.close();
	file.open("sort.dat", std::ios::binary | std::ios::out);

	tmp.close();
	tmp.open("tmp.dat", std::ios::binary | std::ios::in);

	Info data;
	while (!tmp.eof())
	{
		tmp >> data.key;
		file << data.key;
		file << " ";
		tmp >> data.value;
		file << data.value;
	}

	file.close();
	file.open("sort.dat", std::ios::binary | std::ios::in);
	tmp.close();
}


void SaveTreeToFileWithCompare(Node **ptr)
{
	std::fstream tmp("tmp.dat", std::ios::binary | std::ios::out);
	bool doReadNextWord = true;
	Info data;
	data.key = "";
	data.value = 0;
	MergeTreeFile(&(*ptr), doReadNextWord, tmp, data);
	if (!doReadNextWord)
	{
		tmp << data.key;
		tmp << " ";
		tmp << data.value;
	}
	while (!file.eof())
	{
		file >> data.key;
		tmp << data.key;
		tmp << " ";
		file >> data.value;
		tmp << data.value;
	}

	//довыброс дерева
	if (*ptr != nullptr)
	{
		CopyNotSortedTreeToFile(&(*ptr), tmp);
	}

	//кидаем в file из тмп
	CopyDataFile(tmp);
}




void InsertTreeToFile(Node **ptr)
{
	SaveTreeToFileWithCompare(&(*ptr));
	DisposeTree(&(*ptr));
}


void DoSort(Node **ptr)
{
	if (!file.good())
	{
		file.close();
		file.open("sort.dat", std::ios::binary | std::ios::out);
		CopyTreeToFile(&(*ptr));
		DisposeTree(&(*ptr));
		file.close();
		file.open("sort.dat", std::ios::binary | std::ios::in);
	}
	else
	{
		InsertTreeToFile(&(*ptr));
	}
}

void InsertDataInTree(Node **ptr, const Info &data, size_t & num)
{
	Insert(&(*ptr), data, num);
	if (num == MAX_SIZE)
	{
		num = 0;
		DoSort(&(*ptr));
	}
}

void PrintFile(std::ofstream &output)
{

	file.close();
	file.open("sort.dat", std::ios::binary | std::ios::in);
	Info data;
	while (!file.eof())
	{

		file >> data.key;
		output << data.key << " ";
		file >> data.value;
		output << data.value << std::endl;
	}
	file.close();
	file.open("sort.dat", std::ios::binary | std::ios::out);
}
