// ------------------------------------------------------
// This program filters protein-protein interactions
// at a given confidence level from string database
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
	int Cutoff;
	cout << "Enter cutoff score: ";
	cin >> Cutoff;
	cout << " " << endl;

	// Open input file
	ifstream IN(argv[1]);
	if(!IN.is_open()) { cout << "Error: Input File" << endl; exit(1); }

	set<string> Interaction;
	string line;
	while(getline(IN,line))
	{
		stringstream DATA(line);
		string a,b;
		int    c; 
		DATA >> a; 
		DATA >> b;
		DATA >> c;
		
		if(c>=Cutoff)
		{
		ostringstream link1;
		ostringstream link2;
		link1 << a;
		link1 << "\t";
		link1 << b;
		link2 << b;
		link2 << "\t";
		link2 << a;
		Interaction.insert(link1.str());
		Interaction.insert(link2.str());	
		}
		
	}
	IN.close();

	// Open output file
	ofstream OUT(argv[2]);
	if(!OUT.is_open()) { cout << "Error: Output File" << endl; exit(1); }			
	set<string>::iterator it;
	for(it=Interaction.begin();it!=Interaction.end();it++)
	{	
	OUT << *it << endl;
	}
	OUT.close();

return 0;
}
