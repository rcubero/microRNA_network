// This program finds orthology between Human
// and Mouse genes using Homologene database.
// -------------------------------------------
// Program written by: Ryan Cubero & Areejit Samal
// -------------------------------------------
#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[])
{
	ifstream IN(argv[2]);
        if(!IN.is_open()) { cout << "Error: Input File" << endl; exit(1); }

        ofstream OUT(argv[3]);
        if(!OUT.is_open()) { cout << "Error: Output File" << endl; exit(1); }

        string bait;

        while(getline(IN,bait))
        {
                stringstream DATA(bait);
                string GeneSymbol;
                int Entrez;
                double Score;
                DATA >> GeneSymbol;
                DATA >> Entrez;

                ifstream DIC(argv[1]);
                if(!DIC.is_open()) { cout << "Error: Homology Dictionary File" << endl; exit(1); }
                
                string line;
		bool flag=0;
                while(getline(DIC,line))
                {
                        stringstream DICDATA(line);
                        int Human_Entrez, Mouse_Entrez;
                        string  HumanPID, MousePID;

                        DICDATA >> Human_Entrez;
                        DICDATA >> HumanPID;
                        DICDATA >> Mouse_Entrez;
                        DICDATA >> MousePID;
                        
                        if(Entrez==Human_Entrez)
         		{
				OUT << GeneSymbol << "\t" << Entrez << "\t" << Mouse_Entrez << endl;
				flag=1;
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
