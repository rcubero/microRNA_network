// This program computes the Differentially 
// Expressed Genes using data from Giacca Lab. 
// -------------------------------------------
// Program written by: Areejit Samal
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
using namespace std;

int main(int argc, char *argv[])
{

	double threshold=0.0;
	cout << "Enter the threshold: ";
	cin  >> threshold;	

	// Open input file
	ifstream IN(argv[1]);
	if(!IN.is_open()) { cout << "Error: Input File" << endl; exit(1); }

	int UPmiR199=0, DNmiR199=0, UPmiR590=0,  DNmiR590=0, UPboth=0, DNboth=0;	

	string line;
	while(getline(IN,line))
	{
		stringstream DATA(line);
		int a=0;
		DATA >> a; 

		// RPKM > 5
		if(a)
		{

			double empty, cel, miR199, miR590;
			DATA >> empty; 	DATA >> cel; DATA >> miR199; 	DATA >> miR590;		
			double miR199empty, miR199cel, miR590empty, miR590cel, variation;
			DATA >> miR199empty;  DATA >> miR199cel; DATA >> miR590empty;    DATA >> miR590cel; 	DATA >> variation;

			if(variation<=0.2)
			{
			
				bool flag1=0, flag2=0, flag3=0, flag4=0;
				if(miR199empty>=threshold) 	{ UPmiR199++; flag1=1; }
				if(miR590empty>=threshold) 	{ UPmiR590++; flag2=1; }
				if(miR199empty<=(1/threshold)) 	{ DNmiR199++; flag3=1; }
                                if(miR590empty<=(1/threshold)) 	{ DNmiR590++; flag4=1; }
				
				if(flag1 && flag2) UPboth++;
				if(flag3 && flag4) DNboth++;
			}		
		}		
	}	
	IN.close(); 

	cout << "------------------------------" << endl;
	cout << "Results with the threshold " << threshold << endl;
	cout << "------------------------------" << endl;
	cout << "Upregulated miR199: " << UPmiR199 << endl; 
	cout << "Upregulated miR590: " << UPmiR590 << endl;
	cout << "Intersection Upregulated: " << UPboth << endl;
	cout << "Downregulated miR199: " << DNmiR199 << endl; 
	cout << "Downregulated miR590: " << DNmiR590 << endl; 
	cout << "Intersection Downregulated: " << DNboth << endl;
	cout << "------------------------------" << endl;

return 0;
}
