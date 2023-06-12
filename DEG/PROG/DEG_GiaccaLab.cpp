// This program computes the Differentially 
// Expressed Genes using method of Giacca Lab. 
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
	
	// Open output files
	ofstream OUT1(argv[2]);
	if(!OUT1.is_open()) { cout << "Error: Output File 1" << endl; exit(1); }
	ofstream OUT2(argv[3]);
	if(!OUT2.is_open()) { cout << "Error: Output File 2" << endl; exit(1); }
	ofstream OUT3(argv[4]);
	if(!OUT3.is_open()) { cout << "Error: Output File 3" << endl; exit(1); }
	ofstream OUT4(argv[5]);
	if(!OUT4.is_open()) { cout << "Error: Output File 4" << endl; exit(1); }
	ofstream OUT5(argv[6]);
	if(!OUT5.is_open()) { cout << "Error: Output File 5" << endl; exit(1); }
	ofstream OUT6(argv[7]);
	if(!OUT6.is_open()) { cout << "Error: Output File 6" << endl; exit(1); }
	ofstream OUT7(argv[8]);
	if(!OUT7.is_open()) { cout << "Error: Output File 7" << endl; exit(1); }
	ofstream OUT8(argv[9]);
	if(!OUT8.is_open()) { cout << "Error: Output File 8" << endl; exit(1); }

	int UPmiR199=0, DNmiR199=0, UPmiR590=0,  DNmiR590=0, UPboth=0, DNboth=0;	

	string line;
	while(getline(IN,line))
	{
		stringstream DATA(line);
	
		string gi, refseq;
		DATA >> gi;
		DATA >> refseq;

		int a=0; 
		double var=0.0;
		DATA >> a; 
		DATA >> var;

		// RPKM > 5 for empty AND variation <= 0.2
		if(a && (var<=0.2))
		{
			double miR199change, miR590change;
			DATA >> miR199change; 
			DATA >> miR590change;
			
			bool flag1=0, flag2=0, flag3=0, flag4=0;
			if(miR199change >=threshold) 		{ UPmiR199++; flag1=1; }
			if(miR590change >=threshold) 		{ UPmiR590++; flag2=1; }
			if(miR199change <=(1/threshold)) 	{ DNmiR199++; flag3=1; }
                        if(miR590change<=(1/threshold)) 	{ DNmiR590++; flag4=1; }
				
			if(flag1 || flag2) OUT1 << refseq << "\t" << gi << endl;
			if(flag1 && flag2) OUT2 << refseq << "\t" << gi << endl;
			if(flag1) 	   OUT3 << refseq << "\t" << gi << endl;
			if(flag2)          OUT4 << refseq << "\t" << gi << endl;
			if(flag3 || flag4) OUT5 << refseq << "\t" << gi << endl;
			if(flag3 && flag4) OUT6 << refseq << "\t" << gi << endl;
			if(flag3)          OUT7 << refseq << "\t" << gi << endl;
			if(flag4)          OUT8 << refseq << "\t" << gi << endl;
			
			if(flag1 && flag2) UPboth++;
			if(flag3 && flag4) DNboth++;
		}		
	}	
	IN.close(); 
	OUT1.close();
	OUT2.close();	

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
