// This program converts Entrez gene IDs to their
// common names.
// -------------------------------------------------
// Program written by: Areejit Samal and Ryan Cubero
// -------------------------------------------------

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

	// Open output files
	ofstream OUT(argv[3]);
	if(!OUT.is_open()) { cout << "Error: Output File" << endl; exit(1); }			

	string bait;

	while(getline(IN,bait))
	{
		stringstream DATA(bait);
		string GeneSymbol, Score;
		DATA >> GeneSymbol; DATA >> Score;
		
		ifstream DIC(argv[1]);
		if(!DIC.is_open()) { cout << "Error: Dictionary" << endl; exit(1); }
		
		string line;
		bool flag=0;

		while(getline(DIC,line))
		{
			stringstream DICDATA(line);
			string Mouse_Entrez, Mouse_Symbol;
			DICDATA >> Mouse_Entrez; 

			while(DICDATA >> Mouse_Symbol)
			{

			if(GeneSymbol==Mouse_Symbol)
			{
				OUT << GeneSymbol << "\t" << Mouse_Entrez << "\t" << Score << endl;
				flag=1;
				break;
			}

			}
			
			if(flag==1) { break; }			
		}

		if(flag==0) 
		{
			cout << "Not Found: " << GeneSymbol << endl;
		}

		DIC.close();
		
	}	

	IN.close();
	OUT.close();

	return 0;
}
