#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

/*
 * Function Name:	GetRange
 * Description:		gets the range of days to evaluate input data from.
 *					the range value is separated from gains/losses by abort
 *					semicolon
 */
int GetRange(string data)
{
	int range = 0;
	
	std::size_t foundSemiColon = data.find(";");
	
	// make sure that the input data is properly formated.
	if(foundSemiColon == std::string::npos)
	{
		cout << "No range found! Check input file" << endl;
	}
	else
	{
		range = atoi(data.substr(0,foundSemiColon).c_str());
	}
	
	cout << range << endl;
	
	return range;
}

int main(int argc, char *argv[])
{
	// input file
	ifstream ifs(argv[1]);
	
	// a single line of data from the input file
	string data;
	
	// data struct holding data from input text file
	RangeGain input;
	
	int range;
	
	// make sure the input file opens
	if(ifs.is_open() == true)
	{
		while(getline(ifs,data))
		{
			cout << data << endl;
			
			range = GetRange(data);
			
			input = ParseInput(data);
		}
	}
	else
	{
		cout << "Input file error!" << endl;
	}
	
	return 0;
}