// This program reads in the definition for Mouse
// RNAs from mouse.rna.gbff file.
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

	// Open input file
	ifstream IN("DATA/mouse.rna.gbff");
	if(!IN.is_open()) { cout << "Error: Input File" << endl; exit(1); }	

	// Open output file
	ofstream OUT("DATA/Mouse_refseqtid_Definition.txt");
	if(!OUT.is_open()) { cout << "Error: Output File" << endl; exit(1); }

	string line,define,refseqtid;
	
	while(getline(IN,line))
	{	
	
	if(line=="//")
	{			
	OUT << endl;
	}
	else
	{	
		string str1=line.substr(0,10);
		string str2=line.substr(0,7);

		if(str1=="DEFINITION")
		{
			OUT << line.substr(12);			

			while(getline(IN,line))
			{
				string str3=line.substr(0,9);
				if(str3=="ACCESSION")
				{
				break;
				}
				else
				{
				OUT << line.substr(11);
				}				
			}
		}

		if(str2=="VERSION")
		{
			stringstream DATA(line);
			string a,b;
			DATA >> a;
			DATA >> b;
			OUT << "\t" << b;	
		}
	}
		
	}
	IN.close();
	OUT.close();

return 0;
}
