#include "stdafx.h"

#include "validation.h"

using namespace std;

bool IsValidNumOfArguments(int argc)
{
	return (argc == ARGUMENTS_COUNT);
}


bool AreValidInputAndOutputFiles(char * argv[], ifstream &input, ofstream & output)
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
	if (!output.is_open())
	{
		cout << "Failed to open " << argv[2] << " for writing" << "\n";
		return false;
	}
	return true;
}