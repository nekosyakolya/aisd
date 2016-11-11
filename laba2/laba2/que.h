#pragma once

#include <iostream>  
#include <string> 
#include <fstream>
#include <iterator>

struct Spy
{
	std::string name;
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


void CreateQue(Que *spysQue, std::ifstream &input);
void OutputProtocol(Que *spysQue);