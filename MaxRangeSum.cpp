#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	// input file
	ifstream ifs(argv[1]);
	
	if(ifs.is_open() == true)
	{
		cout << "Opened input file!" << endl;
	}
	else
	{
		cout << "Input file error!" << endl;
	}
	
	return 0;
}