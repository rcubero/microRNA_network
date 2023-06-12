// ------------------------------------------------------
// This program picks values for betweenness and degree
// for an input file of converted IDs
//
// Format of Input File:
//   <Common Name>	<STRING ID>
//
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
	ifstream IN(argv[3]);
	if(!IN.is_open()) { cout << "Error: Input File" << endl; exit(1); }

	// Open output file
	ofstream OUT(argv[4]);
	if(!OUT.is_open()) { cout << "Error: Output File" << endl; exit(1); }			

	string input;

	while(getline(IN,input))
	{
		stringstream DATA(input);
		string GeneName, Entrez, RefSeq, GeneID, Degree, Between;
		DATA >> GeneName, DATA >> Entrez; DATA >> RefSeq; DATA >> GeneID; DATA >> Degree; DATA >> Between;
		OUT << input << "\t";

		// Open Alias Dictionary
		ifstream IMPACT(argv[1]);
                if(!IMPACT.is_open()) { cout << "Error: Impact file" << endl; exit(1); }

		string line;
		bool flag=0;

		while(getline(IMPACT,line))
		{
			stringstream IMPACTDATA(line);
			string EntrezID, CommonName, Proliferation;
			IMPACTDATA >> EntrezID; IMPACTDATA >> CommonName; IMPACTDATA >> Proliferation;

			if(Entrez==EntrezID)
			{
				OUT << Proliferation << "\t";
				flag=1;
				break;
			}		
		}

		IMPACT.close();

		if(!flag)
                {
                        OUT << "-" << "\t";
			cout << "Not Found: " << GeneName << endl;
                }

		// Open Alias Dictionary
                ifstream EXP(argv[2]);
                if(!EXP.is_open()) { cout << "Error: Expression file" << endl; exit(1); }

                string line2;
                bool flag1=0;

                while(getline(EXP,line2))
                {
                        stringstream EXPDATA(line2);
                        string RefSeqTID, RefSeqID, miR199, miR590;
                        EXPDATA >> RefSeqTID; EXPDATA >> miR199; EXPDATA >> miR590;

			int found = RefSeqTID.find(".");
	                RefSeqID = RefSeqTID.substr(0,found);

                        if(RefSeq==RefSeqID)
                        {
                                OUT << miR199 << "\t" << miR590 << endl;
                                flag1=1;
                                break;
                        }
                }

                EXP.close();

                if(!flag1)
                {
                        OUT << "-" << "\t" << "-" << endl;
                }


	}	

	IN.close();
	OUT.close(); 

	return 0;
}
