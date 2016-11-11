#pragma once

#include <iostream> 
#include <fstream>
static const int ARGUMENTS_COUNT = 2;

bool IsValidNumOfArguments(int argc);

bool IsValidInputFile(char * argv[], std::ifstream &input);