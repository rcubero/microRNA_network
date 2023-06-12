// ----------------------------------------
// This program converts human miRNA target
// genes to mouse common names
// ----------------------------------------
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
	ifstream IN(argv[1]);
	if(!IN.is_open()) { cout << "Error: Input File" << endl; exit(1); }

	// Open output files
	ofstream OUT(argv[2]);
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
		DATA >> Human_Entrez;
		DATA >> Mouse_Entrez;
		DATA >> Score;

		// Open Dictionary
		ifstream DIC("DATA/Mouse_CommonName.txt");
		if(!DIC.is_open()) { cout << "Error: Mouse Common Name Dictionary" << endl; exit(1); }
		
		string line;
		bool flag=0;

		while(getline(DIC,line))
		{
			stringstream DICDATA(line);
			string MouseSymbol;
			int MouseEntrez;
			
			DICDATA >> MouseEntrez; 
			DICDATA >> MouseSymbol;

			if(Mouse_Entrez==MouseEntrez)
			{
				OUT << miRNA << "\t" << GeneSymbol << "\t" << Human_Entrez << "\t" << MouseSymbol << "\t";
				OUT << MouseEntrez << "\t" << Score << endl;
				flag=1;
				break;
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

	//For Validated Targets
	ifstream INV(argv[3]);
        if(!INV.is_open()) { cout << "Error: Input File" << endl; exit(1); }

        // Open output files
        ofstream OUTV(argv[4]);
        if(!OUTV.is_open()) { cout << "Error: Output File" << endl; exit(1); }

        string baitV;

        while(getline(INV,baitV))
        {
                stringstream DATAV(baitV);

                string miRNA, GeneSymbol;
                int Human_Entrez, Mouse_Entrez;
                double Score;

                DATAV >> miRNA;
                DATAV >> GeneSymbol;
                DATAV >> Human_Entrez;
                DATAV >> Mouse_Entrez;

                // Open Dictionary
                ifstream DIC("DATA/Mouse_CommonName.txt");
                if(!DIC.is_open()) { cout << "Error: Mouse Common Name Dictionary" << endl; exit(1); }

                string lineV;
                bool flagV=0;

                while(getline(DIC,lineV))
                {
                        stringstream DICDATA(lineV);
                        string MouseSymbol;
                        int MouseEntrez;

                        DICDATA >> MouseEntrez;
                        DICDATA >> MouseSymbol;

                        if(Mouse_Entrez==MouseEntrez)
                        {
                                OUTV << miRNA << "\t" << GeneSymbol << "\t" << Human_Entrez << "\t" << MouseSymbol << "\t";
                                OUTV << MouseEntrez << endl;
                                flagV=1;
                                break;
                        }
                }

                if(flagV==0)
                {
                        cout << "Not Found: " << GeneSymbol << endl;
                }

                DIC.close();

        }

        INV.close();
        OUTV.close();

	return 0;
}
