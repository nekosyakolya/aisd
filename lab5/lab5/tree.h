#pragma once
#include <string>
#include <fstream>



static const size_t MAX_SIZE = 5;


struct Info
{
	std::string key;
	unsigned value;
};


struct Node
{
	Node *left;
	Node *right;
	Info data;
	bool insertedInRightPlace;
};


void DisposeTree(Node **root);
void InsertDataInTree(Node **ptr, const Info &data, size_t & num);
void PrintFile(std::ofstream &output);

void InsertTreeToFile(Node **ptr);

