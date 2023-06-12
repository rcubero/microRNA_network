// ------------------------------------------------------
// This program searches for protein-protein interactions
// for an input gene in its common name
//
// Database: STRING database
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
	ofstream REPOSITORY(argv[4]);
	if(!REPOSITORY.is_open()) {cout << "Error: Repository File" << endl; exit(1); }	

	string str;

	while(getline(IN,str))
	{
		stringstream INPUT(str);
		string GeneID, GeneName, RefSeq;
		INPUT >> GeneName; INPUT >> GeneID; INPUT >> RefSeq;
		OUT << str << "\t";

		// Open Alias Dictionary
		ifstream ALIAS(argv[1]);
		if(!ALIAS.is_open()) { cout << "Error: Alias database" << endl; exit(1); }

		string line;
		bool flag1=0;

		while(getline(ALIAS,line))
		{
			stringstream ALIASDATA(line);
			string Aliases, EnsemblID;
			ALIASDATA >> EnsemblID; ALIASDATA >> Aliases;

			string str;

			if(GeneName==Aliases)
			{
				OUT << EnsemblID << endl;
				flag1=1;
				break;
			}		
		}

		ALIAS.close();

		if(!flag1)
                {
			// /*
			//Added by Ryan:Comment if necessary
			// Open already converted dictionary
                	ifstream CONVERT(argv[5]);
                	if(!CONVERT.is_open()) { cout << "Error: Already Converted database" << endl; exit(1); }

                	string line2;
                	bool flag2=0;

                	while(getline(CONVERT,line2))
                	{
                        	stringstream CONVERTDATA(line2);
                        	string Name, a, b, ConvertedID;
                        	CONVERTDATA >> Name; CONVERTDATA >> a; CONVERTDATA >> b; CONVERTDATA >> ConvertedID;

	                       	if(GeneName==Name)
                        	{
                                	OUT << ConvertedID << endl;
                                	flag2=1;
					break;
                        	}
               	 	}

                	CONVERT.close();

			if(!flag2)
			{
				REPOSITORY << GeneName << endl;
                        	OUT << "-" << endl;
                        	cout << "Not Found: " << GeneName << endl;
			}
			// */

			//Commented by Ryan: uncomment if necessary
                        //REPOSITORY << GeneName << endl;
                        //OUT << "-" << endl;
			//cout << "Not Found: " << GeneName << endl;
                }
	}	

	IN.close();
	OUT.close(); 

	return 0;
}
