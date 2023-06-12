// ------------------------------------------------------
// This program expands starting from a given node using 
// protein-protein interactions in STRING database at a 
// given confidence level to determine the set of 
// differentially expressed genes reached via nearest 
// neighbours.
// ------------------------------------------------------
// Program written by: Areejit
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

	vector<string> NODE,NODEcommon;

	// Open interaction file
	{
	ifstream NET(argv[1]);
	if(!NET.is_open()) { cout << "Error: Interaction Network" << endl; exit(1); }
	{	
	set<string> ND;
	string line;
	while(getline(NET,line))
	{
		stringstream DATA(line);
		string a, b;
		DATA >> a;
		ND.insert(a);	
		DATA >> b;
		ND.insert(b);
	}	

	set<string>::iterator it;
	for(it=ND.begin();it!=ND.end();it++)
	{ NODE.push_back(*it); }

	}
	NET.close();	
	}
	cout << "The number of nodes is: " << NODE.size() << endl;

	for(int i=0;i<NODE.size();i++) NODEcommon.push_back("");

	vector< vector<bool> > C;
	{
		vector<bool> temp;
		for(int i=0;i<NODE.size();i++) temp.push_back(0);
		for(int i=0;i<NODE.size();i++) C.push_back(temp);	
	}

	// Open interaction file
	{
	ifstream NET(argv[1]);
        if(!NET.is_open()) { cout << "Error: Interaction Network" << endl; exit(1); }
        string line;
	int count=0;
        while(getline(NET,line))
        {
	count++;
	cout << count << endl;
                stringstream DATA(line);
                string a, b;
                DATA >> a;
	        DATA >> b;
		int i=-1,j=-1;
		for(int k=0;k<NODE.size();k++)
		{
		if(NODE[k]==a) i=k;
		if(NODE[k]==b) j=k;	
		}

		if(i!=-1 && j!=-1)
		{
		C[i][j]=1; C[j][i]=1;
		}
		else
		{
		cout << "Error in interaction: " << line << endl;
		exit(1);
		}	
        }
	NET.close();
	}

        cout << "Read in the interactions in the network" << endl; 


	vector<string> DNG, DNC;
	string line;

	// Open downregulated genes
        ifstream DN(argv[2]);
        if(!DN.is_open()) { cout << "Error: Downregulated genes" << endl; exit(1); }
		
	while(getline(DN,line))
	{	
	stringstream DATA(line);
	string Entrez, Common, Ensembl;
	DATA >> Entrez; 
	DATA >> Common;
	DATA >> Ensembl;
	
	if(Ensembl!="-")
	{
	DNG.push_back(Ensembl);
	DNC.push_back(Common);	
	}
	else
	{
	cout << "DNG - Not in Ensembl: " << Common << endl;
	}	

	}
	DN.close();

	vector<string> UPG, UPC;
        // Open upregulated genes
        ifstream UP(argv[3]);
        if(!UP.is_open()) { cout << "Error: Upregulated genes" << endl; exit(1); }

        while(getline(UP,line))
        {
        stringstream DATA(line);
        string Entrez, Common, Ensembl;
        DATA >> Entrez; 
        DATA >> Common; 
        DATA >> Ensembl;
        
        if(Ensembl!="-")
        {
        UPG.push_back(Ensembl);
	UPC.push_back(Common);
        }
        else
        {
        cout << "UPG - Not in Ensembl: " << Common << endl;
        }

        }
        UP.close();
        
	cout << "Read in the differentially expressed genes" << endl; 
	
	// Mark the differentially expressed genes in string network
	vector<bool> STRING_DG, T1, T2;
	for(int i=0;i<NODE.size();i++) { STRING_DG.push_back(0); T1.push_back(0); T2.push_back(0); }
	
	for(int i=0;i<DNG.size();i++)
	{
		for(int j=0;j<NODE.size();j++)
		{
			if(NODE[j]==DNG[i]) 
			{	 
			STRING_DG[j]=1;
			NODEcommon[j]=DNC[i];
			break;	
			}
		}
	} 

	for(int i=0;i<UPG.size();i++)
        {
                for(int j=0;j<NODE.size();j++)
                {
                        if(NODE[j]==UPG[i])
                        {
                        STRING_DG[j]=1;
			NODEcommon[j]=UPC[i];
                        break;
                        }
                }
        }

	// Open output file 2
	ofstream OUT2(argv[5]);
        if(!OUT2.is_open()) { cout << "Error: Output File 2" << endl; exit(1); }
	for(int i=0;i<NODE.size();i++)
	{
		if(STRING_DG[i])
		{
			for(int j=0;j<NODE.size();j++)
			{
				if(STRING_DG[j])
				{
				if(C[i][j])
				{				
					OUT2 << NODEcommon[i] << "\t" << NODEcommon[j] << endl;
				}
				}
			}
		}

	}
	OUT2.close();

	// Open output file 1
	ofstream OUT1(argv[4]);
	if(!OUT1.is_open()) { cout << "Error: Output File 1" << endl; exit(1); }			
	
	for(int i=0;i<DNG.size();i++)
	{
		bool flag=0;
		for(int j=0;j<NODE.size();j++)
		{
		if(NODE[j]==DNG[i]) { T1[j]=1; T2[j]=0; flag=1; }
		else                { T1[j]=0; T2[j]=0;         }
		}
			
		if(flag)
		{
		
			while(T1!=T2)
			{
			
			for(int j=0;j<NODE.size();j++)
			{
			if(T2[j]) T1[j]=1;
			}
	
			for(int j=0;j<NODE.size();j++)
			{		
				if(T1[j])
				{
				T2[j]=T1[j];

					for(int k=0;k<NODE.size();k++)
					{
						if(C[j][k])
						{
						if(STRING_DG[k]) T2[k]=1;	
						}
					}	
				}	
			}

			}
	
			int sum=0;
			for(int j=0;j<NODE.size();j++) if(T1[j]) sum++;		

			OUT1 << DNC[i] << "\t" << DNG[i] << "\t" << sum << "\t";
			for(int j=0;j<NODEcommon.size();j++) if(T1[j]) OUT1 << NODEcommon[j] << " ";
			OUT1 << endl;
		}
		else
		{
			OUT1 << DNC[i] << "\t" << DNG[i] << "\t" << "1" << "\t" << "-" << endl; 
		}
	}
	OUT1.close();

return 0;
}
