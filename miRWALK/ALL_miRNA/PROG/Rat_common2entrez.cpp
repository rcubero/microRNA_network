// -----------------------------------------
// This program converts rat common names
// to rat Entrez IDs using Rat_alias.txt
// -----------------------------------------

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
	// For Predicted Targets	
	// Open input file
	ifstream IN("DATA/Rat_Data/Predicted_rno-miR.txt");
	if(!IN.is_open()) { cout << "Error: Input File" << endl; exit(1); }

	// Open output files
	ofstream OUT(argv[1]);
	if(!OUT.is_open()) { cout << "Error: Output File" << endl; exit(1); }			

	string bait;

	while(getline(IN,bait))
	{
		stringstream DATA(bait);

		string miRNA, GeneSymbol; 
		int Human_Entrez, Rat_Entrez;
		double Score;
		
		DATA >> GeneSymbol;
		DATA >> miRNA;
		DATA >> Score;

		// Open Dictionary
		ifstream DIC("DATA/Rat_Data/Rat_AliasFile.txt");
		if(!DIC.is_open()) { cout << "Error: Rat Aliases Dictionary" << endl; exit(1); }
		
		string line;
		bool flag=0;

		while(getline(DIC,line))
		{
			stringstream DICDATA(line);
			string RatSymbol;
			int RatEntrez;
			
			DICDATA >> RatEntrez; 
			while(DICDATA >> RatSymbol)
			{
				if(GeneSymbol==RatSymbol)
				{
					OUT << miRNA << "\t" << GeneSymbol << "\t" << RatEntrez << "\t" << Score << endl;
					flag=1;
					break;
				}		
				if(flag==1) break;
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
