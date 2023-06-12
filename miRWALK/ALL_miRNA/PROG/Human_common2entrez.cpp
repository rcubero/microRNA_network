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

	// Open output files
	ofstream OUT(argv[2]);
	if(!OUT.is_open()) { cout << "Error: Output File" << endl; exit(1); }			

	string bait;

	while(getline(IN,bait))
	{
		stringstream DATA(bait);
		string miRNA, GeneSymbol, Score;
		DATA >> GeneSymbol; DATA >> miRNA; DATA >> Score;
		
		ifstream DIC("DATA/Rat_Data/Human_AliasFile.txt");
		if(!DIC.is_open()) { cout << "Error: Dictionary" << endl; exit(1); }
		
		string line;
		bool flag=0;

		while(getline(DIC,line))
		{
			stringstream DICDATA(line);
			string Human_Entrez, Human_Symbol;
			DICDATA >> Human_Entrez; 

			while(DICDATA >> Human_Symbol)
			{

			if(GeneSymbol==Human_Symbol)
			{
				OUT << miRNA << "\t" << GeneSymbol << "\t" << Human_Entrez << "\t" << Score << endl;
				flag=1;
				break;
			}
			
			}
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
