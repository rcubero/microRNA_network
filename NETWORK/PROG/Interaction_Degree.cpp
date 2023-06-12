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
	double Cutoff=0.0;
	cout << "Enter cutoff score: ";
	cin >> Cutoff;
	cout << " " << endl;

	// Open input file
	ifstream IN(argv[1]);
	if(!IN.is_open()) { cout << "Error: Input File" << endl; exit(1); }

	// Open output file
	ofstream OUT(argv[2]);
	if(!OUT.is_open()) { cout << "Error: Output File" << endl; exit(1); }			
	ofstream REPOSITORY(argv[3]);
	if(!REPOSITORY.is_open()) {cout << "Error: Repository File" << endl; exit(1); }	
	ofstream COUNTER(argv[4]);
	if(!COUNTER.is_open()) {cout << "Error: Count File" << endl; exit(1); }

	string GeneName;

	while(IN >> GeneName)
	{
		// Open Alias Dictionary
		ifstream ALIAS(argv[1]);
		if(!ALIAS.is_open()) { cout << "Error: Alias database" << endl; exit(1); }

		string line;
		string StringID;
		bool flag1=0;

		while(getline(ALIAS,line))
		{
			stringstream ALIASDATA(line);
			string EnsemblID, Aliases;
			ALIASDATA >> EnsemblID; ALIASDATA >> Aliases;

			string str;

			if(GeneName==Aliases)
			{
				StringID = EnsemblID;
				flag1=1;
				break;
			}		
		}

		ALIAS.close();

		if(!flag1)
                {
                        REPOSITORY << GeneName << endl;
                        cout << "Not Found: " << GeneName << endl;
                }

		//Open Interaction Dictionary
	        ifstream DIC(argv[2]);
	        if(!DIC.is_open()) { cout << "Error: Interaction database" << endl; exit(1); }

	        string linksline;
        	bool flag2=0;
		int count=0;

	        while(getline(DIC,linksline))
        	{
                	stringstream DATA(linksline);
	        	string EnsemblID1, EnsemblID2;
			double Score=0.0;
	                DATA >> EnsemblID1; DATA >> EnsemblID2; DATA >> Score;

	                if((StringID==EnsemblID1) && (Score>=Cutoff))
	                {
	                	OUT << GeneName << "\t" << EnsemblID1 << "\t" << EnsemblID2 << "\t" << Score << endl;
	                        flag2=1;
	                        count++;
        	        }

	        }
	
		COUNTER << GeneName << "\t" << count << endl;

        	DIC.close();

		if(!flag2 && flag1) 
		{ 
			cout << "No Interaction Found: " << GeneName << endl; 
		}
	}	

	IN.close();
	OUT.close(); 

	return 0;
}
