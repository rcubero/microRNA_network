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
        ofstream REPOSITORY(argv[4]);
        if(!REPOSITORY.is_open()) { cout << "Error: Output File - Unconverted Genes" << endl; exit(1); }

	int NotFound=0;
	string bait;
	while(getline(IN,bait))
	{
		stringstream DATA(bait);
		string Refseq, Entrez;
		DATA >> Refseq;
		DATA >> Entrez;	
		
		// Open Dictionary
		ifstream DIC(argv[1]);
		if(!DIC.is_open()) { cout << "Error: Dictionary" << endl; exit(1); }
		
		string line;
		bool flag=0;

		while(getline(DIC,line))
		{
			stringstream DICDATA(line);
			string a, b;
			DICDATA >> a; DICDATA >> b;

			if(Entrez==a)
			{
				OUT << b << "\t" << Entrez << "\t" << Refseq << endl;
				flag=1;
				break;
			}		
		}
		if(flag==0) 
		{
		NotFound++;
		REPOSITORY << Refseq << endl; 
		}
		DIC.close();
		
	}	

	IN.close();
	OUT.close();
	REPOSITORY.close(); 

	cout << "-----------------------" << endl;
	cout << "Not Found: " << NotFound << endl;
	cout << "-----------------------" << endl;
	return 0;
}
