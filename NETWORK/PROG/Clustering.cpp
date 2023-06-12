// This program computes the transitivity (clustering
// coefficient) of the nodes of a graph using igraph
// library. 
// ------------------------------------------------
// Program written by: 
// Areejit Samal (asamal@ictp.it)
// Ryan Cubero
// ------------------------------------------------
// INPUT FORMAT:
// The input file should list the links in the
// network, one link per line, as follows:
// nodeA nodeB
// nodeA nodeC
// nodeC nodeB
// ...........
// ------------------------------------------------	
// igraph is open source library which can be directly
// installed in Ubuntu using Synaptic Package Manager
// sudo apt-get install libigraph0
// igraph manual is available at:
// http://igraph.sourceforge.net/doc/html/index.html
// ------------------------------------------------
#include <igraph.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

int main(int argc,char *argv[])
{

// Open input file containing the set of links
std::fstream IN(argv[1]);
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

 std::stringstream DATA(line);
 std::vector<std::string> Link;
 std::string str;	
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
		k=NodeName.size()-1; 
	}
	Edge.push_back(k);

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
		k=NodeName.size()-1; 
	}
	Edge.push_back(k);

	}

 }
 else
 {
 std::cout << "Error in Input file at line number: " << linenum << std::endl;	
 }  
}		
IN.close();

// Print the number of edges in the graph
int NumNode = NodeName.size();	
long int NumEdge = Edge.size();
std::cout << "The number of nodes is: " << NumNode << " and the number of edges is: " << NumEdge/2 << std::endl; 
std::cout << "******************************************" << std::endl;

// Open output file 
std::ofstream OUT(argv[2]);
if(!OUT.is_open()) { std::cout << "Error: Output" << std::endl; exit(1); }

// igraph graph object
igraph_t graph;

// Create an igraph vector for edges
igraph_vector_t v;
igraph_vector_init(&v,NumEdge);

// Enter the elements of the vector into igraph object
for(int i=0;i<Edge.size();i++)
{
VECTOR(v)[i]=Edge[i];
}

// Load the graph
igraph_create(&graph,&v,NumNode,1); 
	
// Remove multiple edge from the graph
// igraph_simplify(&graph,1,0); // Commented by Santhust; Next line added
igraph_simplify(&graph,1,1,0);

// Compute the clustering coefficient of nodes
igraph_vector_t clustering;
igraph_vector_init(&clustering,NumNode);
igraph_transitivity_local_undirected(/*graph=*/&graph, /*res=*/&clustering, /*vids=*/igraph_vss_all(), /*mode=*/IGRAPH_TRANSITIVITY_ZERO);

// Output the clustering coefficient of each node in descending order
igraph_real_t temp;
for(int i=0;i<NumNode;i++)
{
	long int k=igraph_vector_which_max(&clustering);
	OUT << NodeName[k] << "\t" << VECTOR(clustering)[k] << std::endl;
	VECTOR(clustering)[k] = -10;
}
OUT.close();

return 0;
}
