/*
   16. У множества шпионов,  собравшихся вместе для наблюдения
секретного     объекта,    имеется    единственный    бинокль.
Сформировалась очередь на этот  бинокль.  Для  каждого  шпиона
задан   период   наблюдения   в  минутах  и  предельное  время
нахождения в очереди. После наблюдения каждый шпион становится
снова  в  конец  очереди.  Как  только  для какого-либо шпиона
истекает предельное время нахождения в очереди, он покидает ее
(даже  если  в  этот момент владеет биноклем) и отправляется к
резиденту. Вывести протокол наблюдения шпионов за объектом(9).Красильникова Ольга ПС-21*/


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