// This program finds the variant number 
// using definition for refseq transcript id. 
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

	// Open input file
	ifstream IN(argv[1]);
	if(!IN.is_open()) { cout << "Error: Input File" << endl; exit(1); }
	
	// Open output file
	ofstream OUT(argv[2]);
	if(!OUT.is_open()) { cout << "Error: Output File" << endl; exit(1); }			

	string line;
	while(getline(IN,line))
	{
	
		stringstream DATA(line);
		bool flag=0; string str;
		while(DATA >> str)	
		{
			if(str=="variant") 
			{
			string a;
			DATA >> a;
			OUT << a << endl;
			flag=1;
			break;
			}
		}
		
		if(!flag) 
		{
		OUT << "_" << endl;
		}
				
	}	
	IN.close();
	OUT.close(); 

return 0;
}
