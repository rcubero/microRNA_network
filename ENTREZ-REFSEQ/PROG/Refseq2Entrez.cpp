// This program converts Refseq Nucleotide IDs to
// Entrez IDs using the following dictionaries:
//
// current dictionary:
//   for mouse: Mouse_Entrez_refseq_tid.txt
//   for human: Human_Entrez_refseq_tid.txt
//
// suppressed dictionary:
//   dictionary must have the format 
//   <Entrez> <Refseq NucAccession>
//
//
// Notes:
//  input file must be a list of 
// to compile:
// g++ Refseq2Entrez.cpp -o REFSEQ2ENTREZ
//
// to run:
// ./REFSEQ2ENTREZ <current dictionary> <suppressed dictionary>
//   <input file> <output file> <repository for unconverted ID>
//
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
	ifstream IN(argv[3]);
	if(!IN.is_open()) { cout << "Error: Input File" << endl; exit(1); }

	// Open output file
	ofstream OUT(argv[4]);
	if(!OUT.is_open()) { cout << "Error: Output File" << endl; exit(1); }			
        ofstream REPOSITORY(argv[5]);
        if(!REPOSITORY.is_open()) { cout << "Error: Output File - Unconverted Genes" << endl; exit(1); }
	
	string Refseq;
	int NotFound=0;

	while(IN >> Refseq)
	{
		OUT << Refseq << "\t";

		// Open Dictionary
		ifstream DIC(argv[1]);
		if(!DIC.is_open()) { cout << "Error: Dictionary" << endl; exit(1); }
		ifstream SUPPRESSED(argv[2]);
		if(!SUPPRESSED.is_open()) { cout << "Error: Dictionary of Suppressed IDs" << endl; exit(1); }

		string line, line2;
		bool flag1=0, flag2=0;

		while(getline(DIC,line))
		{
			stringstream DICDATA(line);
			string a, b;
			DICDATA >> a; DICDATA >> b;

			if(Refseq==b)
			{
				OUT << a << endl;
				flag1=1;
				break;
			}		
		}

		DIC.close();

		if(!flag1)
		{
			while(getline(SUPPRESSED,line2))
			{
				stringstream SUPDATA(line2);
				string c, d;
				SUPDATA >> c; SUPDATA >> d;

				if(Refseq==d)
				{
					OUT << c << endl;
					flag2=1;
					break;
				}
			}
			
			SUPPRESSED.close();

			if(!flag2)
			{
				OUT << '-' << endl;
				REPOSITORY << Refseq << endl;
				cout << "Not Found: " << Refseq << endl;
				NotFound++;
			}
		}	
	}	

	IN.close();
	OUT.close();
	REPOSITORY.close(); 

	cout << "-----------------------" << endl;
	cout << "Not Found: " << NotFound << endl;
	cout << "-----------------------" << endl;
	return 0;
}
