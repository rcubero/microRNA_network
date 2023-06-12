// This program finds orthology between Human
// and Mouse genes using Homologene.
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
	int human = 9606;	
       	int chimp = 9598;
	int monkey = 9544;
	int dog = 9615;
	int cattle = 9913;
	int mouse = 10090;
	int rat = 10116;
	
	// Open output file
	ofstream OUT("DATA/ConservationHumanGene.txt");
	if(!OUT.is_open()) { cout << "Error: Output File" << endl; exit(1); }

	// Open input file with group ids
	ifstream GP("DATA/homologene.group");
	if(!GP.is_open()) { cout << "Error: Group Number File" << endl; exit(1); }	

	int gp=0;
	while(GP >> gp)
	{
	cout << gp << endl;

		vector<string> humanE;
		vector<string> mouseE;
		vector<string> chimpE;		
		vector<string> monkeyE;
		vector<string> dogE;
		vector<string> cattleE;
		vector<string> ratE;	
		
		// Open homology data file
		ifstream HOM("DATA/homologene.data");
		if(!HOM.is_open()) { cout << "Error: Homology Data" << endl; exit(1); }	
		string line;
		while(getline(HOM,line))
		{
			stringstream DATA(line);
			int id, taxid;
			string  entrezid, gname, gipid, refseqpid;
			DATA >> id;
			if(id==gp)
			{		
				DATA >> taxid;
				DATA >> entrezid;
						
				if(taxid==human) humanE.push_back(entrezid);
				if(taxid==mouse) mouseE.push_back(entrezid);
				if(taxid==rat) ratE.push_back(entrezid);
				if(taxid==chimp) chimpE.push_back(entrezid);
				if(taxid==monkey) monkeyE.push_back(entrezid);
				if(taxid==cattle) cattleE.push_back(entrezid);
				if(taxid==dog) dogE.push_back(entrezid);		
			
			}
		}		
		HOM.close();


		if(!humanE.empty())
		{
			
			for(int i=0;i<humanE.size();i++)	
			{
			OUT << humanE[i] << "\t";

				// Conservation Score 
				int count=0;
				if(mouseE.size()>0) count++;
				if(ratE.size()>0) count++;	
				if(chimpE.size()>0) count++;
				if(monkeyE.size()>0) count++;
				if(cattleE.size()>0) count++;
				if(dogE.size()>0) count++;
			
				OUT << (double (count))/6 << "\t";

				// Homologs from Homologene		 
				for(int j=0;j<mouseE.size();j++) OUT << mouseE[j] << " ";
				OUT << "\t";		
				for(int j=0;j<ratE.size();j++) OUT << ratE[j] << " ";
				OUT << "\t";	
				for(int j=0;j<chimpE.size();j++) OUT << chimpE[j] << " ";
				OUT << "\t";	
				for(int j=0;j<monkeyE.size();j++) OUT << monkeyE[j] << " ";
				OUT << "\t";	
				for(int j=0;j<cattleE.size();j++) OUT << cattleE[j] << " ";
				OUT << "\t";	
				for(int j=0;j<dogE.size();j++) OUT << dogE[j] << " ";
				OUT << endl;	
	
			}			

		}

	}
	GP.close();
  	OUT.close(); 

return 0;
}
