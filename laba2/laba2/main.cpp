/*
   16. � ��������� �������,  ����������� ������ ��� ����������
����������     �������,    �������    ������������    �������.
�������������� ������� �� ����  �������.  ���  �������  ������
�����   ������   ����������   �  �������  �  ����������  �����
���������� � �������. ����� ���������� ������ ����� ����������
�����  �  �����  �������.  ���  ������  ��� ������-���� ������
�������� ���������� ����� ���������� � �������, �� �������� ��
(����  ����  �  ���� ������ ������� ��������) � ������������ �
���������. ������� �������� ���������� ������� �� ��������(9).������������� ����� ��-21*/


#include "stdafx.h"
#include "que.h"
#include "validation.h"

using namespace std;

int main(int argc, char * argv[])
{
	setlocale(LC_ALL, "");

	if (!IsValidNumOfArguments(argc))
	{
		cout << "Invalid arguments count\n"
			<< "Usage: laba2.exe <input file> \n";
		return EXIT_FAILURE;
	}  

	ifstream input(argv[1]);

	ofstream output(argv[2]);
	if (!AreValidInputAndOutputFiles(argv, input, output))
	{
		return EXIT_FAILURE;
	}

	Que *spysQue = new Que;
	spysQue->begQue = nullptr;
	spysQue->endQue = nullptr;
	spysQue->curr = nullptr;

	CreateQue(spysQue, input);

	OutputProtocol(spysQue, output);

    return EXIT_SUCCESS;
}