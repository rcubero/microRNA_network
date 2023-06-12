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

	//Predicted human targets	
	ifstream IN(argv[1]);
        if(!IN.is_open()) { cout << "Error: Input File" << endl; exit(1); }

        ofstream OUT(argv[2]);
        if(!OUT.is_open()) { cout << "Error: Output File" << endl; exit(1); }

        string bait;

        while(getline(IN,bait))
        {
                stringstream DATA(bait);
                string miRNA, GeneSymbol;
                int Entrez;
                double Score;
		DATA >> miRNA;
                DATA >> GeneSymbol;
                DATA >> Entrez;
		DATA >> Score;

                ifstream DIC("DATA/Human2Rat_MinimalModel.txt");
                if(!DIC.is_open()) { cout << "Error: Homology Dictionary File for Minimal Model" << endl; exit(1); }
                
                string line;
		bool flag=0;
                while(getline(DIC,line))
                {
                        stringstream DICDATA(line);
                        int Human_Entrez;
			string Mouse_Entrez;
                        string HumanPID, MousePID;

			DICDATA >> HumanPID;
                        DICDATA >> Human_Entrez;
                        DICDATA >> MousePID;
                        DICDATA >> Mouse_Entrez;
                        
                        if((Entrez==Human_Entrez)&&(Mouse_Entrez!=""))
         		{
				//OUT << miRNA << "\t" << GeneSymbol << "\t" << Entrez << "\t" << Mouse_Entrez << "\t" << Score << endl;
				OUT << miRNA << "\t" << MousePID << "\t" << Mouse_Entrez << "\t" << Score << endl;
				flag=1;
			}

		}

		if(flag==0)
        	{
       	        	cout << "Predicted Not Found: " << GeneSymbol << endl;
                }

                DIC.close();

        }

        IN.close();
        OUT.close();
               

	//Validated human targets
        ifstream INV(argv[3]);
        if(!INV.is_open()) { cout << "Error: Input File" << endl; exit(1); }

        ofstream OUTV(argv[4]);
        if(!OUTV.is_open()) { cout << "Error: Output File" << endl; exit(1); }

        string baitV;

        while(getline(INV,baitV))
        {
                stringstream DATAV(baitV);
                string miRNA, GeneSymbol;
                int Entrez;
                DATAV >> GeneSymbol;
                DATAV >> Entrez;
		DATAV >> miRNA;

                ifstream DIC("DATA/Human2Rat_MinimalModel.txt");
                if(!DIC.is_open()) { cout << "Error: Homology Dictionary File" << endl; exit(1); }

                string lineV;
                bool flagV=0;
                while(getline(DIC,lineV))
                {
                        stringstream DICDATAV(lineV);
                        int Human_Entrez;
			string Mouse_Entrez;
                        string  HumanPID, MousePID;

			DICDATAV >> HumanPID;
                        DICDATAV >> Human_Entrez;
                        DICDATAV >> MousePID;
                        DICDATAV >> Mouse_Entrez;

                        if((Entrez==Human_Entrez)&&(Mouse_Entrez!=""))
                        {
                                OUTV << miRNA << "\t" << MousePID << "\t" << Mouse_Entrez << endl;
                                flagV=1;
                        }

                }

                if(flagV==0)
                {
                        cout << "Validated Not Found: " << GeneSymbol << endl;
                }

                DIC.close();

        }

        INV.close();
        OUTV.close();

	return 0;
}
