#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "windows.h"
#include <conio.h>
struct Node
{
	std::string name;
	Node *left;
	Node *right;
	Node *father;
	size_t level;
	bool isFile;
};


void OutputToFile(Node *root, std::ostream & output);


void Delete(Node **root);

void RecalculationLevel(Node **root);


void OutputData(Node *tmp);


Node *Open(Node **tmp, bool & isIt);

Node *Search(Node ** tmp, bool & isIt);




Node *Create(Node **tmp, const bool& isFile);


Node *CopyElement(Node *tmp, Node *father);


void AddNewElement(Node **tmp, bool &isOpen, const bool& isFile);

void ReadTree(Node **root, std::istream & input);


void OutputInfo(Node **tmp, const bool & isOpen);
void OpenData(Node **tmp, bool & isOpen, const bool & isIt);



void CloseData(Node **tmp, bool & isOpen, Node **root);

void DeleteThisElement(Node **tmp, bool & isOpen);


void RenameElement(Node **tmp, Node **root, bool & isOpen);

