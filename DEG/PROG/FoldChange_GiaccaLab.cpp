// This program computes fold change for RNAseq 
// data from Giacca Lab. 
// -------------------------------------------
// Program written by: Areejit Samal
// Edited by: Ryan Cubero
// -------------------------------------------
#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <cstdlib>
#include <iterator>
#include <algorithm>
#include <cmath>
using namespace std;

int main(int argc, char *argv[])
{

	// Open input file
	ifstream IN(argv[1]);
	if(!IN.is_open()) { cout << "Error: Input File" << endl; exit(1); }

	// Open output file
	ofstream OUT(argv[2]);
	if(!OUT.is_open()) { cout << "Error: Output File" << endl; exit(1); }			

	string line;
	while(getline(IN,line))
	{

		stringstream DATA(line);
		string gi, refseq;	
		DATA >> gi; DATA >> refseq;
		double empty, cel, miR590, miR199;
		DATA >> empty; 	DATA >> cel; DATA >> miR590; 	DATA >> miR199;		
	
		// Compute Variation
		double variation=0.0;
		variation = 2.0*(abs(cel - empty))/(cel + empty);	

		// Threshold
		bool flag=0;
		if( (empty>=5.0) )
		{
		flag=1;
		}			

		OUT << gi << "\t" << refseq << "\t" << flag << "\t" << variation << "\t";
		
		// Fold Change
		if(flag)
		{
			if(miR199 > empty) OUT << (miR199)/(empty) << "\t";
			else OUT << -(empty)/(miR199) << "\t";

			if(miR590 > empty) OUT << (miR590)/(empty) << "\t";
			else OUT << -(empty)/(miR590) << "\t";

		}
		else
		{
			OUT << "-\t-\t";
		}
		
			OUT << miR199 << "\t" << miR590 << "\t" << empty << "\t" << cel << endl;
		
	}	
	IN.close();
	OUT.close(); 

return 0;
}
