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
#include <iostream>  
#include <string> 
#include <fstream>
#include <iterator>


using namespace std;


struct Spy
{
	string name;
	unsigned timeInQue;
	unsigned timeForOqular;
	Spy *prev;
	Spy *next;
};


struct Que
{
	Spy *begQue;
	Spy *endQue;
	Spy *curr;
};

static const int ARGUMENTS_COUNT = 2;

void AddQ(Que *spysQue, const string spyName, const unsigned &timeFor, const unsigned &timeQue)
{
	Spy *spy = new Spy;
	spy->name = spyName;
	spy->timeForOqular = timeFor;
	spy->timeInQue = timeQue;

	if (spysQue->begQue != nullptr)
	{
		spy->prev = spysQue->curr;
		spysQue->curr->next = spy;
		spysQue->curr = spy;
	}
	else
	{
		spy->prev = nullptr;
		spysQue->begQue = spy;
		spysQue->curr = spy;
	}
	spysQue->endQue = spy;
	spy->next = nullptr;
}

void DeleteQ(Que *spysQue, const unsigned &timeSpy, unsigned &timeSpyForOqular)
{
	cout << "Шпион " << spysQue->begQue->name << " сейчас смотрит в бинокль" << endl;
	spysQue->curr = spysQue->begQue;


	while (spysQue->curr != nullptr)
	{
		if (spysQue->curr->timeInQue == timeSpy)
		{
			cout << "Шпион " << spysQue->curr->name << " ушел из очереди" << endl;
			if (spysQue->begQue == spysQue->endQue)
			{
				delete(spysQue->begQue);
				spysQue->begQue = nullptr;
				spysQue->endQue = nullptr;
				spysQue->curr = nullptr;
			}
			else if (spysQue->curr == spysQue->begQue)
			{
				spysQue->begQue = spysQue->begQue->next;
				delete(spysQue->begQue->prev);
				spysQue->begQue->prev = nullptr;
				spysQue->curr = spysQue->begQue;
				timeSpyForOqular = 0;
			}
			else if (spysQue->curr == spysQue->endQue)
			{
				spysQue->endQue = spysQue->endQue->prev;
				delete(spysQue->endQue->next);
				spysQue->endQue->next = nullptr;
				spysQue->curr = spysQue->endQue;
			}
			else
			{
				spysQue->curr->prev->next = spysQue->curr->next;
				spysQue->curr->next->prev = spysQue->curr->prev;
				Spy *tmp = spysQue->curr;
				spysQue->curr = spysQue->curr->prev;
				delete(tmp);
			}
		}
		
			else if (spysQue->curr != nullptr)
			{
				spysQue->curr = spysQue->curr->next;
			}
		
	}
}

bool IsValidNumOfArguments(int argc)
{
	return (argc == ARGUMENTS_COUNT);
}


bool IsValidInputFile(char * argv[], ifstream &input)
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
	return true;
}

void CreateQ(Que *spysQue, ifstream &input)
{
	string spyName;
	unsigned timeFor;
	unsigned timeQue;
	while (input >> spyName)
	{
		input >> timeFor;
		input >> timeQue;
		if (timeFor > 0 && timeQue > 0)
		{
			AddQ(spysQue, spyName, timeFor, timeQue);
		}
	}
}

void OutputResults(Que *spysQue)
{
	for (unsigned timeSpy = 1, timeSpyForOqular = 1; (spysQue->begQue != nullptr); ++timeSpy, ++timeSpyForOqular)
	{
		cout << "Текущее время: " << timeSpy << endl;
		spysQue->curr = spysQue->begQue;

		if ((spysQue->curr->timeForOqular == timeSpyForOqular) && (spysQue->begQue != spysQue->endQue))
		{
			spysQue->curr = spysQue->begQue;
			cout << "Шпион " << spysQue->curr->name;
			cout << " ушел в конец очереди" << endl;
			spysQue->begQue = spysQue->curr->next;
			spysQue->curr->prev = spysQue->endQue;
			spysQue->curr->next = nullptr;
			spysQue->endQue->next = spysQue->curr;
			spysQue->endQue = spysQue->curr;
			spysQue->begQue->prev = nullptr;
			timeSpyForOqular = 0;
		}

		DeleteQ(spysQue, timeSpy, timeSpyForOqular);

		cout << endl;
	}
}

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
	if (!IsValidInputFile(argv, input))
	{
		return EXIT_FAILURE;
	}

	Que *spysQue = new Que;
	spysQue->begQue = nullptr;
	spysQue->endQue = nullptr;
	spysQue->curr = nullptr;

	CreateQ(spysQue, input);

	OutputResults(spysQue);

    return EXIT_SUCCESS;
}