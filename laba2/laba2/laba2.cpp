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
#include <ctime>


using namespace std;


struct Spy
{
	string name;
	unsigned timeInQue;
	Spy *prev;
	Spy *next;
};


struct Que
{
	Spy *begQue;
	Spy *endQue;
	Spy *curr;
};


static const unsigned TIME_FOR_OQULAR = 2;
static const unsigned TIME_SPY_MAX = 10;

void AddQ(Que *spysQue, const string spyName)
{
	Spy *spy = new Spy;
	spy->name = spyName;
	spy->timeInQue = rand() % (TIME_SPY_MAX - 1) + TIME_FOR_OQULAR;

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

void DeleteQ(Que *spysQue, const unsigned &timeSpy, unsigned timeSpyForOqular)
{
	spysQue->curr = spysQue->begQue;
	while (spysQue->curr != nullptr)
	{
		if (spysQue->curr->timeInQue == timeSpy)
		{
			cout << "Шпион " << spysQue->curr->name << " ушел из очереди" << endl;
			timeSpyForOqular = 0;
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
		if (spysQue->curr == spysQue->endQue)
		{
			spysQue->curr = nullptr;
		}
		else if (spysQue->curr != nullptr)
		{
			spysQue->curr = spysQue->curr->next;
		}
	}
}

int main(int argc, char * argv[])
{
	setlocale(LC_ALL, "");
	static const int maxNumberOfArgument = 2;

	if (argc != maxNumberOfArgument)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: laba2.exe <input file> \n";
		return EXIT_FAILURE;
	}  

	ifstream input(argv[1]);

	if (!input.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return EXIT_FAILURE;
	}

	Que *spysQue = new Que;
	spysQue->begQue = nullptr;
	spysQue->endQue = nullptr;
	spysQue->curr = nullptr;


	
	srand(unsigned(time(NULL)));
	string spyName;
	while (input >> spyName)
	{
		AddQ(spysQue, spyName);

	}
	unsigned timeSpyForOqular = 0;
	for (unsigned timeSpy = 1; ((timeSpy <= TIME_SPY_MAX) && spysQue->begQue != nullptr); ++timeSpy, ++timeSpyForOqular)
	{
		cout << "Текущее время: " << timeSpy << endl;
		if ((timeSpyForOqular % TIME_FOR_OQULAR == 0) && (timeSpyForOqular != 0) && (spysQue->begQue != spysQue->endQue))
		{
			spysQue->curr = spysQue->begQue;
			cout << "Шпион " << spysQue->begQue->name;
			cout << " ушел в конец очереди" << endl;
			spysQue->begQue = spysQue->curr->next;
			spysQue->curr->prev = spysQue->endQue;
			spysQue->curr->next = nullptr;
			spysQue->endQue->next = spysQue->curr;
			spysQue->endQue = spysQue->curr;        
			spysQue->begQue->prev = nullptr;
			timeSpyForOqular = 0;
		}
		cout << "Шпион " << spysQue->begQue->name << " сейчас смотрит в бинокль" << endl;
		
		DeleteQ(spysQue, timeSpy, timeSpyForOqular);
		
	    cout << endl;
	}
	
    return EXIT_SUCCESS;
}