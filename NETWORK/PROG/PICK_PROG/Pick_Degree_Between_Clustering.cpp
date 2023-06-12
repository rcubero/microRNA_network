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
		string GeneName, Entrez, RefSeq, GeneID; 
		DATA >> GeneName; DATA >> Entrez; DATA >> RefSeq; DATA >> GeneID;
		OUT << input << "\t";

		// Open Alias Dictionary
		ifstream DEGREE(argv[1]);
                if(!DEGREE.is_open()) { cout << "Error: Degree file" << endl; exit(1); }
		ifstream BETWEEN(argv[2]);
		if(!BETWEEN.is_open()) { cout << "Error: Betweenness centrality file" << endl; exit(1); }
		ifstream CLUSTER(argv[3]);
                if(!CLUSTER.is_open()) { cout << "Error: Clustering file" << endl; exit(1); }

		string line1;
		bool flag1=0;

		while(getline(DEGREE,line1))
		{
			stringstream DEGDAT(line1);
			string EnsemblID, Degree;
			DEGDAT >> EnsemblID; DEGDAT >> Degree;

			if(GeneID==EnsemblID)
			{
				OUT << Degree << "\t";
				flag1=1;
				break;
			}		
		}

		DEGREE.close();

		if(!flag1)
                {
                        OUT << "-" << "\t";
                }

		string line2;
                bool flag2=0;

                while(getline(BETWEEN,line2))
                {
                        stringstream BETDAT(line2);
                        string EnsemblID2, Between;
                        BETDAT >> EnsemblID2; BETDAT >> Between;

                        if(GeneID==EnsemblID2)
                        {
                                OUT << Between << endl;
                                flag2=1;
                                break;
                        }
                }

                BETWEEN.close();

                if(!flag2)
                {
                        OUT << "-" << endl;
                }

		string line3;
                bool flag3=0;

                while(getline(CLUSTER,line3))
                {
                        stringstream CLUSDAT(line3);
                        string EnsemblID3, Clustering;
                        BETDAT >> EnsemblID3; BETDAT >> Clustering;

                        if(GeneID==EnsemblID3)
                        {
                                OUT << Clustering << endl;
                                flag3=1;
                                break;
                        }
                }

                CLUSTER.close();

                if(!flag3)
                {
                        OUT << "-" << endl;
                }
	}	

	IN.close();
	OUT.close(); 

	return 0;
}
