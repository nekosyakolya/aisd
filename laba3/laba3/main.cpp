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

#include "validation.h"

#include "tree.h"
#include "const.h"

using namespace std;


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
		case ENTER:
			OpenData(&tmp, isOpen, isIt);
			isBegin = true;
			break;
		case ESC:
			CloseData(&tmp, isOpen, &root);
			isBegin = true;
			break;
		case SPACE:
			OutputMenu();
			break;
		case PLUS:
			if (tmp != root)
			{
				AddNewElement(&tmp, isOpen, true);
			}
			isBegin = true;
			break;
		case MULTIPLICATION://*
			if (tmp != root)
			{
				AddNewElement(&tmp, isOpen, false);
			}
			isBegin = true;
			break;
		case DEL:
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
		case ONE://1
			RenameElement(&tmp, &root, isOpen);
			isBegin = true;
			break;
		case BACKSPACE://переместиь backspace
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
		case INSERT://вставить insert
			if (node != nullptr  && tmp->father != nullptr)
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
		case TAB://copy tab
		{
			p = tmp;
			Node *father = new Node;
			father->father = nullptr;
			father->left = nullptr;
			father->right = nullptr;
			father->isFile = false;
			father->level = 0;
			father->name = "";
			if (tmp == root || (tmp->father == root && isOpen))
			{

				node = CopyElement(root, father);
			}
			else if (!isOpen)
			{

				node = CopyElement(tmp, father);
				tmp = tmp->father->left;
			}
			else
			{
				node = CopyElement(tmp->father, father);
			}
			tmp = p;
			isBegin = true;
		}
			break;
		case DOWN:
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
		case UP:
			if (tmp->father != nullptr)
			{
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
			}
			break;
		default:
			break;
		}
	}
	while (userAnswer != END && root != nullptr);


	OutputToFile(root, output);
	return EXIT_SUCCESS;
}




