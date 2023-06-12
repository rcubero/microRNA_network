// -----------------------------------------
// This program converts mouse common names
// to mouse Entrez IDs using Mouse_alias.txt
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
	ifstream IN("DATA/Predicted_mmu-miR.txt");
	if(!IN.is_open()) { cout << "Error: Input File" << endl; exit(1); }

	// Open output files
	ofstream OUT(argv[1]);
	if(!OUT.is_open()) { cout << "Error: Output File" << endl; exit(1); }			

	string bait;

	while(getline(IN,bait))
	{
		stringstream DATA(bait);

		string miRNA, GeneSymbol; 
		int Human_Entrez, Mouse_Entrez;
		double Score;
		
		DATA >> miRNA;
		DATA >> GeneSymbol;
		DATA >> Score;

		// Open Dictionary
		ifstream DIC("DATA/Mouse_alias.txt");
		if(!DIC.is_open()) { cout << "Error: Mouse Aliases Dictionary" << endl; exit(1); }
		
		string line;
		bool flag=0;

		while(getline(DIC,line))
		{
			stringstream DICDATA(line);
			string MouseSymbol;
			int MouseEntrez;
			
			DICDATA >> MouseEntrez; 
			while(DICDATA >> MouseSymbol)
			{
				if(GeneSymbol==MouseSymbol)
				{
					OUT << miRNA << "\t" << GeneSymbol << "\t" << MouseEntrez << "\t" << Score << endl;
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
