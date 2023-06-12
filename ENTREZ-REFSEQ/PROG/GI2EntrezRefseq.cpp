// This program converts genbank IDs to entrez
// and refseq IDs using gene2refseq.
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

	string str;
	while(IN >> str)
	{
		// Open gene2refseq file
		ifstream DIC(argv[1]);
		if(!DIC.is_open()) { cout << "Error: Dictionary" << endl; exit(1); }		
		bool flag=0;	
		string line;
		set<string> entrez;
		set<string> refseqt;
		set<string> refseqp;
		while(getline(DIC,line))	
		{

		stringstream DATA(line);
		string taxid, entrezid, refseqtid, refseqpid, gi, empty;
		DATA >> taxid;
		DATA >> entrezid;	
		DATA >> empty;	
		DATA >> refseqtid;
		DATA >> gi;
		DATA >> refseqpid;
				
			if(str==gi)
			{
			flag=1;
			entrez.insert(entrezid);
			refseqt.insert(refseqtid);
			refseqp.insert(refseqpid);
			}		
		}		
		DIC.close();

		if(!flag)
		{
		cout << "Not found: " << str << endl;
		OUT << str << "\t0" << endl;
		}	
		else
		{
			OUT << str << "\t1\t";
			set<string>::iterator it;
			for(it=refseqt.begin();it!=refseqt.end();it++)
			{
			OUT << *it << " ";
			}		
			OUT << "\t";
			for(it=refseqp.begin();it!=refseqp.end();it++)
			{
			OUT << *it << " ";
			}		
			OUT << "\t";
			for(it=entrez.begin();it!=entrez.end();it++)
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

