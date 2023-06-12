// ------------------------------------------------------
// This program picks values for betweenness and degree
// for an input file of converted IDs
// ------------------------------------------------------
// Program written by: Ryan Cubero
// ------------------------------------------------------

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
	ifstream IN(argv[2]);
	if(!IN.is_open()) { cout << "Error: Input File" << endl; exit(1); }

	// Open output file
	ofstream OUT(argv[3]);
	if(!OUT.is_open()) { cout << "Error: Output File" << endl; exit(1); }			

	string input;

	while(getline(IN,input))
	{
		stringstream DATA(input);
		string GeneName, StringID, Factor;
		DATA >> GeneName, DATA >> StringID; DATA >> Factor;
		OUT << input << "\t";

		// Open Alias Dictionary
		ifstream DIC(argv[1]);
                if(!DIC.is_open()) { cout << "Error: Impact file" << endl; exit(1); }

		string line;
		bool flag=0;

		while(getline(DIC,line))
		{
			stringstream DICDATA(line);
			string a, String, Impact;
			DICDATA >> a; DICDATA >> a; DICDATA >> a; DICDATA >> String; 
			DICDATA >> a; DICDATA >> a; DICDATA >> Impact; DICDATA >> a; DICDATA >> a;

			if(String==StringID)
			{
				OUT << Impact << endl;
				flag=1;
				break;
			}		
		}

		DIC.close();

		if(!flag)
                {
                        OUT << "-" << endl;
			cout << "Not Found: " << GeneName << endl;
                }
	}	

	IN.close();
	OUT.close(); 

	return 0;
}
