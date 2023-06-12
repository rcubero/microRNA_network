// This program computes the degree of nodes in a graph.
// ------------------------------------------------
// Program written by: 
// Areejit Samal (asamal@ictp.it) 
// ------------------------------------------------
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc,char *argv[])
{

// Open input file containing the set of links
std::ifstream IN(argv[1]);
if(!IN.is_open()) { std::cout << "Error: Input" << std::endl; exit(1); }
	
// Open a vector to store node names in the graph
std::vector<std::string> NodeName;
std::vector<int> Edge;
std::string line;	

// Each line of the input file specifies an edge
int linenum=0;
while(getline(IN,line))
{
linenum++;

 stringstream DATA(line);
 vector<string> Link;
 string str;	
 while(DATA >> str) { Link.push_back(str); }

 if(Link.size()==2)
 {	

	// Determine the source node	
	{	

	int k=-1;
	bool flag=0;
	for(int i=0;i<NodeName.size();i++)
	{			
		if(NodeName[i]==Link[0]) 
		{
		k=i;
		flag=1;
		break;
		}	
	}
		if(!flag) 
		{ 
		NodeName.push_back(Link[0]);
		Edge.push_back(0); 
		k=NodeName.size()-1; 
		}
 		Edge[k]++;
	}
	
	// Determine the target node	
	{	

	int k=-1;
	bool flag=0;
	for(int i=0;i<NodeName.size();i++)
	{			
		if(NodeName[i]==Link[1]) 
		{
		k=i;
		flag=1;
		break;
		}	
	}
		if(!flag)
                { 
                NodeName.push_back(Link[1]); 
                Edge.push_back(0);
                k=NodeName.size()-1; 
                }
                Edge[k]++;
	}

 }
 else
 {
 cout << "Error in Input file at line number: " << linenum << endl;	
 }  
}		
IN.close();

// Open output file 
ofstream OUT(argv[2]);
if(!OUT.is_open()) { cout << "Error: Output" << endl; exit(1); }
for(int i=0;i<NodeName.size();i++)
{
OUT << NodeName[i] << "\t" << (Edge[i]/2) << endl;	
}
OUT.close();

return 0;
}
