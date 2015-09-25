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

/*
 * Function Name:	GetGains
 * Description:		parse the string of text that has gains/losses separated by a space
 */
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
		
		// loop until the end of the input string
		while(findSpace != std::string::npos)
		{
			gainValues = sGains.substr(0,findSpace);
			
			gains.push_back(atoi(gainValues.c_str()));
			
			sGains = sGains.substr(findSpace+1);
			
			findSpace = sGains.find(" ");
			
			//cout << gains.back() << endl;
		}
		
		//ugly hack
		gains.push_back(atoi(sGains.c_str()));
		
		//cout << gains.back() << endl;
	}
	
	return gains;
}

/*
 * Function Name:	MaxGain
 * Description:		Calculate the max gain of the input text over a given range
 */
int MaxGain(int range, vector<int> gains)
{
	int maxGain = 0;
	int tempGain = 0;
	
	unsigned int index = 0;
	unsigned int subIndex = 0;	 
	unsigned int gainSize = (unsigned int)gains.size()-range+1;
	
	//cout << gainSize << endl;
	
	while(index < gainSize)
	{
		//cout << gains[index] << endl;
		
		while(subIndex < (unsigned int)range)
		{		
			//cout << gains[index+subIndex] << "+";
			
			tempGain = tempGain + gains[index+subIndex];
			
			++subIndex;
		}
		
		//cout << " Temp Gain: " << tempGain << endl;
		
		if(tempGain > maxGain)
		{
			maxGain = tempGain;
		}
		
		tempGain = 0;
		subIndex = 0;
		
		++index;
	}
	
	return maxGain;
} 
 

int main(int argc, char *argv[])
{
	// input file
	ifstream ifs(argv[1]);
	
	// a single line of data from the input file
	string data;
	
	int range = 0;	
	int index = 1;	
	int maxGain = 0;
	
	vector<int> gains;
	
	// make sure the input file opens
	if(ifs.is_open() == true)
	{
		while(getline(ifs,data))
		{
			//cout << data << endl;
			
			range = GetRange(data);
			
			if(range != -1)
			{
				gains = GetGains(data);
				
				maxGain = MaxGain(range, gains);
				
				cout << maxGain << endl;
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