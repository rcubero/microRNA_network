// This program converts refseq IDs to ensembl
// gene and transcript IDs using gene2ensembl.
// -------------------------------------------
// Program written by: Areejit Samal
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
	ifstream IN(argv[2]);
	if(!IN.is_open()) { cout << "Error: Input File" << endl; exit(1); }

	// Open output file
	ofstream OUT(argv[3]);
	if(!OUT.is_open()) { cout << "Error: Output File" << endl; exit(1); }			

	string bait;
	while(getline(IN,bait))
	{

		stringstream READ(bait);
		string str1, str2;
		READ >> str1; READ >> str2;

		// Open gene2ensembl file
		ifstream DIC(argv[1]);
		if(!DIC.is_open()) { cout << "Error: Dictionary" << endl; exit(1); }		
		bool flag=0;	
		string line;
		set<string> ensemblg;
		set<string> ensemblt;
		set<string> ensemblp;
		while(getline(DIC,line))	
		{

		stringstream DATA(line);
		string taxid, entrezid, ensemblgid, ensembltid, ensemblpid, refseqtid, refseqpid;
		DATA >> taxid;
		DATA >> entrezid;	
		DATA >> ensemblgid;	
		DATA >> refseqtid;
		DATA >> ensembltid;
		DATA >> refseqpid;	
		DATA >> ensemblpid;
				
			if(str1==refseqtid && str2==refseqpid)
			{
			flag=1;
			ensemblg.insert(ensemblgid);
			ensemblt.insert(ensembltid);
			ensemblp.insert(ensemblpid);
			}		
		}		
		DIC.close();

		if(!flag)
		{
		cout << "Not found: " << str1 << "\t" << str2 << endl;
		OUT << str1 << "\t" << str2 << "\t \t \t" << endl;
		}	
		else
		{
			OUT << str1 << "\t" << str2 << "\t";
			set<string>::iterator it;
			for(it=ensemblg.begin();it!=ensemblg.end();it++)
			{
			OUT << *it << " ";
			}		
			OUT << "\t";
			for(it=ensemblt.begin();it!=ensemblt.end();it++)
			{
			OUT << *it << " ";
			}		
			OUT << "\t";
			for(it=ensemblp.begin();it!=ensemblp.end();it++)
			{
			OUT << *it << " ";
			}		
			OUT << endl;			
		}
	}	
	IN.close();
	OUT.close(); 

return 0;
}
