//10. Имеется  текстовый  файл  записей  с некоторым  ключевым
//полем.Отсортировать файл путем совмещения методов внутренней
//и внешней сортировок(10).Красильникова О.группа ПС-21

#include "stdafx.h"

#include "tree.h"

#include "validation.h"


using namespace std;



void ReadAndSortInputFile(Node **root, ifstream &input)
{
	Info data;
	data.key = "";
	data.value = 0;
	size_t num = 0;
	while (!input.eof())
	{
		input >> data.key;
		input >> data.value;
		InsertDataInTree(&(*root), data, num);
	}
	//довыброс дерева
	if (*root != nullptr)
	{
		InsertTreeToFile(&(*root));
	}
}


int main(int argc, char * argv[])
{

	if (!IsValidNumOfArguments(argc))
	{
		cout << "Invalid arguments count\n"
			<< "Usage: laba5.exe <input file> <output file>\n";
		return EXIT_FAILURE;
	}

	ifstream input(argv[1]);

	ofstream output(argv[2]);
	if (!AreValidInputAndOutputFiles(argv, input, output))
	{
		return EXIT_FAILURE;
	}

	Node *root = new Node;
	root->left = nullptr;
	root->right = nullptr;
	
	root = nullptr;

	ReadAndSortInputFile(&root, input);

	PrintFile(output);

	return EXIT_SUCCESS;
}

