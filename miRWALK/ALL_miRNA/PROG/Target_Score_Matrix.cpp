#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[])
{
	vector<string> DNG;	
	vector<string> DNN;
	vector<string> MIR;
	vector<double> SC;
	vector<double> IMP;

	//Open miRNA file
	ifstream MIRDATA("DATA/TopMicroRNA.txt");
	if(!MIRDATA.is_open()) { cout << "Error: miRNA file" << endl; exit(1); }
	
	cout << "Reading top microRNA file..." << endl;

	string line;
	while(getline(MIRDATA,line))
	{
		bool flag=0;
		for(int i=0;i<MIR.size();i++)
		{
			if(MIR[i]==line)
			{
				SC[i]=0.0;
				flag=1;
				break;
			}
		}
		if(!flag)
		{
			MIR.push_back(line);
			SC.push_back(0.0);
		}
	}
	MIRDATA.close();

	//Open list of downregulated genes
	ifstream DN("DATA/MinimalModel.txt");
	if(!DN.is_open()) { cout << "Error: List of Genes in the minimal model" << endl; exit(1); }
	
	cout << "Reading list of downregulated genes..." << endl;

	string cline;	
	while(getline(DN,cline))
	{
		stringstream DATA(cline);
		string Name, ID;
		double Impact;
		DATA >> Name; DATA >> ID;
		
		bool flag=0;
		for(int i=0;i<DNG.size();i++)
		{
			if(DNG[i]==ID)
			{
				DNN[i]=Name;
				flag=1;
				break;
			}
		}
		if(!flag)
		{
			DNG.push_back(ID);
			DNN.push_back(Name);
		}
	}
	DN.close();


	//Open output file
	ofstream OUT("OUTPUT/RAT_DATA/RatData_TargetScores.txt");
	if(!OUT.is_open()) { cout << "Error: Output File" << endl; exit(1); }	

	cout << "Creating output file..." << endl;

	//Create Header
	OUT << "Gene" << "\t" << "Entrez ID";
	for(int i=0; i<MIR.size(); i++)
	{
		OUT << "\t" << MIR[i];
	}
	OUT << endl;

	//Go through every downregulated gene on the list
	for(int i=0; i<DNG.size(); i++)
        {
                OUT << DNN[i] << "\t" << DNG[i];

		for(int j=0; j<MIR.size(); j++)
		{
			// Look for scores in the dictionary		
			bool flag_mir=0;

			//Open dictionary of targets
	        	ifstream VAL("OUTPUT/RAT_DATA/Validated_Rat_MicroRNA.txt");
       			if(!VAL.is_open()) { cout << "List of all validated miRNA targets" << endl; exit(1); }
	        
			string line_val;

			while(getline(VAL,line_val))
			{
				stringstream VAL_DATA(line_val);

				string miR_ID, GeneName, Entrez;
				VAL_DATA >> miR_ID;
				VAL_DATA >> GeneName;
				VAL_DATA >> Entrez;
				
				if((DNG[i]==Entrez)&&(MIR[j]==miR_ID))
				{
					SC[j]=1.0;
					flag_mir=1;
					break;
				}
			}
			VAL.close();

			//Open dictionary of predicted targets
			ifstream PRED("OUTPUT/RAT_DATA/Predicted_Rat_MicroRNA.txt");
                        if(!PRED.is_open()) { cout << "List of predicted miRNA targets" << endl; exit(1); }
                
                        string line_pred;

                        while(getline(PRED,line_pred))
                        {
                                stringstream PRED_DATA(line_pred);

                                string miR_ID, GeneName, Entrez;
                                int Score;

                                PRED_DATA >> miR_ID;
                                PRED_DATA >> GeneName;
                                PRED_DATA >> Entrez;
                                PRED_DATA >> Score;

				if((DNG[i]==Entrez)&&(MIR[j]==miR_ID))
				{
					double pred_score = double(Score)/10.0;
					if(SC[j]<pred_score)
					{
						SC[j]=pred_score;
					}
					flag_mir=1;
					//break;
				}
			}
			PRED.close();
	
			if(!flag_mir)
			{
				SC[j]=0.0;
			}
		}


		for(int k=0; k<MIR.size(); k++)
		{
			OUT << "\t" << SC[k];
		}
		
		OUT <<endl;
	}

	OUT.close();	

	cout << "Program finished!" << endl;

	return 0;
}
