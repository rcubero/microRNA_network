// ------------------------------------------------------
// This program picks values for betweenness and degree
// for an input file of converted IDs
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
	ifstream IN(argv[2]);
	if(!IN.is_open()) { cout << "Error: Input File" << endl; exit(1); }

	// Open output file
	ofstream OUT(argv[3]);
	if(!OUT.is_open()) { cout << "Error: Output File" << endl; exit(1); }			

	string input;

	while(getline(IN,input))
	{
		stringstream DATA(input);
		string GeneName, Entrez, RefSeq, a;
		DATA >> GeneName, DATA >> Entrez; DATA >> RefSeq; DATA >> a; DATA >> a; DATA >> a; DATA >> a; DATA >> a; DATA >> a;
		OUT << input << "\t";

		// Open Alias Dictionary
		ifstream SCORE(argv[1]);
                if(!SCORE.is_open()) { cout << "Error: Impact file" << endl; exit(1); }

		string line;
		bool flag=0;

		while(getline(SCORE,line))
		{
			stringstream SCOREDATA(line);
			string CommonName, EntrezID, Score;
			SCOREDATA >> CommonName; SCOREDATA >> EntrezID; SCOREDATA >> Score;

			if(Entrez==EntrezID)
			{
				OUT << Score << endl;
				flag=1;
				break;
			}		
		}

		SCORE.close();

		if(!flag)
                {
                        OUT << "0" << endl;
			cout << "Not Found: " << GeneName << endl;
                }

	}	

	IN.close();
	OUT.close(); 

	return 0;
}
