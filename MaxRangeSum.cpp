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
	
	//range and gains/losses are separated by a semicolon
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

vector<int> GetGains(string data)
{
	vector<int> gains;
	
	//range and gains/losses are separated by a semicolon
	std::size_t foundSemiColon = data.find(";");
	std::size_t findSpace;
	
	string sGains;
	string gainValues;

	// make sure that the input data is properly formated.
	if(foundSemiColon == std::string::npos)
	{
		cout << "No range found! Check input file" << endl;
	}
	else
	{
		// +1 to ignore the ;
		sGains = data.substr(foundSemiColon+1,data.size());
		
		findSpace = sGains.find(" ");
		
		while(findSpace != std::string::npos)
		{
			gainValues = sGains.substr(0,findSpace);
			
			gains.push_back(atoi(gainValues.c_str()));
			
			sGains = sGains.substr(findSpace+1);
			
			findSpace = sGains.find(" ");
			
			cout << gains.back() << endl;
		}
		
		gains.push_back(atoi(sGains.c_str()));
		
		cout << gains.back() << endl;
	}
	
	return gains;
}

int main(int argc, char *argv[])
{
	// input file
	ifstream ifs(argv[1]);
	
	// a single line of data from the input file
	string data;
	
	int range = 0;
	
	int index = 1;
	
	vector<int> gains;
	
	// make sure the input file opens
	if(ifs.is_open() == true)
	{
		while(getline(ifs,data))
		{
			cout << data << endl;
			
			range = GetRange(data);
			
			if(range != -1)
			{
				gains = GetGains(data);
			}
			else
			{
				cout << "Error with range for input data set: " << index << endl;
			}
			
			++index;
		}
	}
	else
	{
		cout << "Input file error!" << endl;
	}
	
	return 0;
}