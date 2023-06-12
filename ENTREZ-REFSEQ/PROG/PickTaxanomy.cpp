// This program picks lines for a given taxid. 
// -------------------------------------------
// Program written by: Areejit Samal
// -------------------------------------------
#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <cstdlib>
#include <iterator>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[])
{

	int taxid=atoi(argv[1]);

	// Open input file
	ifstream IN(argv[2]);
	if(!IN.is_open()) { cout << "Error: Input File" << endl; exit(1); }

	// Open output file
	ofstream OUT(argv[3]);
	if(!OUT.is_open()) { cout << "Error: Output File" << endl; exit(1); }			

	string line;
	while(getline(IN,line))
	{

		stringstream DATA(line);
		int a;
		DATA >> a;
		
		if(a==taxid)
		{
		OUT << line << endl;
		}			
		
	}	
	IN.close();
	OUT.close(); 

return 0;
}

