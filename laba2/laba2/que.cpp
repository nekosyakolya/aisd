#include "stdafx.h"
#include "que.h"

using namespace std;

void AddQue(Que *spysQue, const string spyName, const unsigned &timeObservation, const unsigned &timeInQue)
{
	Spy *spy = new Spy;
	spy->name = spyName;
	spy->timeForOqular = timeObservation;
	spy->timeInQue = timeInQue;

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

void ControlQueueTime(Que *spysQue, const unsigned &timeSpy, unsigned &timeSpyForOqular, ofstream &output, bool &wasChanges)
{
	spysQue->curr = spysQue->begQue;


	while (spysQue->curr != nullptr)
	{
		if (spysQue->curr->timeInQue == timeSpy)
		{
			if (!wasChanges)
			{
				output << "������� �����: " << timeSpy << endl;
			}
			output << "����� " << spysQue->curr->name << " ���� �� �������" << endl;
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
				output << "����� " << spysQue->begQue->name << " ������ ������� � �������" << endl;
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

		else
		{
			spysQue->curr = spysQue->curr->next;
		}
	}
}


bool IsValidTime(int timeObservation, int timeInQue)
{
	return (timeObservation > 0 && timeInQue > 0);
}

void CreateQue(Que *spysQue, ifstream &input)
{
	string spyName;
	unsigned timeObservation;
	unsigned timeInQue;
	while (input >> spyName)
	{
		input >> timeObservation;
		input >> timeInQue;
		if (IsValidTime(timeObservation, timeInQue))
		{
			AddQue(spysQue, spyName, timeObservation, timeInQue);
		}
	}
}

void ControlObservationTime(Que *spysQue, const unsigned &timeSpy, unsigned &timeSpyForOqular, ofstream &output, bool &wasChanges)
{
	spysQue->curr = spysQue->begQue;

	if ((spysQue->curr->timeForOqular == timeSpyForOqular) && (spysQue->begQue != spysQue->endQue))
	{
		wasChanges = true;
		output << "������� �����: " << timeSpy << endl;
		output << "����� " << spysQue->curr->name;
		output << " ���� � ����� �������" << endl;
		spysQue->begQue = spysQue->curr->next;

		output << "����� " << spysQue->begQue->name << " ������ ������� � �������" << endl;

		spysQue->curr->prev = spysQue->endQue;
		spysQue->curr->next = nullptr;
		spysQue->endQue->next = spysQue->curr;
		spysQue->endQue = spysQue->curr;
		spysQue->begQue->prev = nullptr;
		timeSpyForOqular = 0;
	}
}

void OutputProtocol(Que *spysQue, ofstream &output)
{
	bool wasChanges = false;
	unsigned timeSpy = 0;
	output << "������� �����: " << timeSpy << endl;
	output << "����� " << spysQue->begQue->name << " ������ ������� � �������" << endl;
	for (unsigned timeSpyForOqular = 0; (spysQue->begQue != nullptr); ++timeSpy, ++timeSpyForOqular)
	{
		ControlObservationTime(spysQue, timeSpy, timeSpyForOqular, output, wasChanges);
		ControlQueueTime(spysQue, timeSpy, timeSpyForOqular, output, wasChanges);
		wasChanges = false;
	}
}
