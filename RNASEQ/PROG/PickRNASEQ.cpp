// This program picks lines for a Giacca Lab
// RNAseq analyzed file. 
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
	
		// Open RNAseq Processed Data
		ifstream AN("DATA/GiaccaLab_miR_RNAseq_ProcessedData.txt");
		if(!AN.is_open()) { cout << "Error: RNAseq" << endl; exit(1); }
		string line;
		bool flag=0;
		while(getline(AN,line))	
		{

			stringstream DATA(line);
			string a, b, c;
			DATA >> a; DATA >> b; DATA >> c;
		
			if(c==str) 
			{
			OUT << line << endl;
			flag=1;
			break;
			}
		}
		AN.close();
		if(!flag) 
		{
		OUT << endl;	
		cout << "Not Found: " << str << endl;
		}
				
	}	
	IN.close();
	OUT.close(); 

return 0;
}
