// This program picks refseq transcript ids 
// without version and gives the transcrip id 
// with version.
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

	string str;
	while(IN >> str)
	{
		OUT << str << "\t";	
	
		// Open Dictionary
		ifstream DIC("refseqtid_version.txt");
		if(!DIC.is_open()) { cout << "Error: Dictionary" << endl; exit(1); }

		string line;
		bool flag=0;
		while(getline(DIC,line))	
		{
			stringstream DATA(line);
			string a, b;
			DATA >> a; DATA >> b;
		
			if(a==str) 
			{
			OUT << b << " ";
			flag=1;
			break;
			}
		}
		DIC.close();
		
		OUT << endl;	
		
		if(!flag) 
		{
		cout << "Not Found: " << str << endl;
		}
				
	}	
	IN.close();
	OUT.close(); 

return 0;
}
