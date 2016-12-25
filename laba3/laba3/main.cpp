//21. ����������  �  ������  ��  �������  ������   ����������
//��������  �  �������  ������.���������� ���������� ���������
//�������� :
//1) �������� ������ � ������ �� �����;
//2) ����� ������ ����� �  ������  �������(��������� �����,
//������ �� ������� � �.�.);
//3) �������������  ������ ��� �������� ����� ����� � ������,
//�� ��������������, �����������, �������� � ��������.
//4) ���������� ������ � �����(13).

#include "stdafx.h"

#include "validation.h"

#include "tree.h"
#include "const.h"

using namespace std;


void OutputMenu()
{
	cout << "������� Enter ��� �������� " << endl
		<< "������� Esc ��� �������� " << endl
		<< "������� + ��� �������� ������ ����� � ������� ����������" << endl
		<< "������� * ��� �������� ����� ����� � ������� ����������" << endl
		<< "������� 1 ����� ������������� ������� ����(�����)" << endl
		<< "������� Delete ����� ������� ������� ����(�����)" << endl
		<< "������� Backspace ����� ����������� ������� ����(�����)" << endl
		<< "������� Insert ����� �������� ����(�����)� ������� ����������" << endl
		<< "������� Tab ����� ����������� ������� ����(�����)" << endl;
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
			cout << "������� End ��� ������ �� ���������" << endl;
			cout << "������� ������ ��� �������" << endl << endl;
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
				cout << "�� ������� ������" << endl;
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
		case BACKSPACE://���������� backspace
			if (tmp == root || (tmp->father == root && isOpen))
			{
				cout << "������ ����������� ������" << endl;
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

					// ��� ���� ����� �� �����
					tmp = tmp->father;

					tmp->father->left = tmp->right;
					p = (tmp->right == nullptr) ? tmp->father : tmp->right;

					tmp = p;
				}
				else
				{
					//�� ������ �������
					// ��� ���� ����� �� �����

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
		case INSERT://�������� insert
			if (node != nullptr  && tmp->father != nullptr)
			{
				if (!isOpen && tmp->isFile)
				{

					cout << "�� �� ������ �������� ������� � ����" << endl;
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
				cout << "�� ���������� �: ";
				if (tmp->father != nullptr)
				{
					cout << tmp->father->name << endl;
				}
				cout << "��������: " << endl;

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
					cout << "�� ���������� �: ";
					if (tmp->father != nullptr)
					{
						cout << tmp->father->name << endl;
					}
					cout << "��������: " << endl;
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




