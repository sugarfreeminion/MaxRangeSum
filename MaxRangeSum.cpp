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
	int range = -1;
	
	std::size_t foundSemiColon = data.find(";");
	
	// make sure that the input data is properly formated.
	if(foundSemiColon == std::string::npos)
	{
		cout << "No range found! Check input file" << endl;
	}
	else
	{
		range = atoi(data.substr(0,foundSemiColon).c_str());
		
		// error checking. range must be between 0 and 10000
		if(range < 0 || range > 10000)
		{
			range = -1;
		}
	}
	
	return range;
}

int main(int argc, char *argv[])
{
	// input file
	ifstream ifs(argv[1]);
	
	// a single line of data from the input file
	string data;
	
	int range = 0;
	
	// make sure the input file opens
	if(ifs.is_open() == true)
	{
		while(getline(ifs,data))
		{
			cout << data << endl;
			
			range = GetRange(data);
			
			cout << range << endl;
		}
	}
	else
	{
		cout << "Input file error!" << endl;
	}
	
	return 0;
}