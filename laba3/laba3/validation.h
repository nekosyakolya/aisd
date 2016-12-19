#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "windows.h"
#include <conio.h>

static const int ARGUMENTS_COUNT = 3;

bool IsValidNumOfArguments(int argc);

bool AreValidInputAndOutputFiles(char * argv[], std::ifstream &input, std::ofstream & output);


