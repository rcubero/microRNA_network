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
        int mtaxid=10116, htaxid=9606;

	// Open output file
	ofstream OUT("DATA/Human2Rat_Homologene_June2014.txt");
	if(!OUT.is_open()) { cout << "Error: Output File" << endl; exit(1); }

	// Open input file with group ids
	ifstream GP("DATA/NCBI_DATABASE/homologene.group");
	if(!GP.is_open()) { cout << "Error: Group Number File" << endl; exit(1); }	

	int gp=0;
	while(GP >> gp)
	{
	cout << gp << endl;

		vector<string> HumanE;
		vector<string> HumanP;	
		vector<string> MouseE;
		vector<string> MouseP;		
	
		// Open homology data file
		ifstream HOM("DATA/NCBI_DATABASE/homologene_June2014.data");
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
				DATA >> gname;
				DATA >> gipid;
				DATA >> refseqpid;
		
				if(taxid==mtaxid)
				{
				MouseE.push_back(entrezid);
				MouseP.push_back(refseqpid);
				}
				if(taxid==htaxid)
				{
				HumanE.push_back(entrezid);
				HumanP.push_back(refseqpid);
				}
			}
		}		
		HOM.close();


		if(!HumanE.empty())
		{
			
			for(int i=0;i<HumanE.size();i++)	
			{
				
				if(!MouseE.empty())
				{
					for(int j=0;j<MouseE.size();j++)	
					{	
					OUT << HumanE[i] << "\t" << HumanP[i] << "\t";			
					OUT << MouseE[j] << "\t" << MouseP[j] << endl;
					}				
				}
				// Reason why there are empty entries in orthology file
				/*else
				{
				OUT << HumanE[i] << "\t" << HumanP[i] << "\t";
				OUT << " \t " << endl;				
				}*/	
			}			

		}


	}
	GP.close();
  	OUT.close(); 

return 0;
}
