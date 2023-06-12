// This program picks refseq transcript ids 
// corresponding to Entrez gene.
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

	// Open input file 1
	ifstream IN1(argv[1]);
	if(!IN1.is_open()) { cout << "Error: Input File 1" << endl; exit(1); }
	
	// Open output file
	ofstream OUT(argv[3]);
	if(!OUT.is_open()) { cout << "Error: Output File" << endl; exit(1); }			

	string str;
	while(IN1 >> str)
	{
		OUT << str << "\t";	
	
		// Open input file 2
		ifstream IN2(argv[2]);
		if(!IN2.is_open()) { cout << "Error: Input File 2" << endl; exit(1); }

		string line;
		bool flag=0;
		while(getline(IN2,line))	
		{
			stringstream DATA(line);
			string a, b;
			DATA >> a; DATA >> b;
		
			if(a==str) 
			{
			OUT << b << " ";
			flag=1;
			}
		}
		IN2.close();
		
		OUT << endl;	
		
		if(!flag) 
		{
		cout << "Not Found: " << str << endl;
		}
				
	}	
	IN1.close();
	OUT.close(); 

return 0;
}
