// This program merges the validated and predicted
// miRNA-gene interactions from the miRWALK database.
// --------------------------------------------------
// Program written by: Areejit Samal
// --------------------------------------------------
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
		
	vector<string> TG;
	vector<double> SC;

	// Open input file 1 - Mouse Validated
	ifstream IN1(argv[1]);
	if(!IN1.is_open()) { cout << "Mouse Validated" << endl; exit(1); }	

	string line;
	while(getline(IN1,line))
	{
		stringstream DATA(line);
		string a;
		for(int i=0;i<4;i++)		
		{
		DATA >> a;
		}
			
		bool flag=0;
		for(int i=0;i<TG.size();i++)
		{
			if(TG[i]==a)
			{
			SC[i]=1.0;
			flag=1;
			break;
			}
		}	

		if(!flag)
		{
		TG.push_back(a);
		SC.push_back(1.0);
		}		
	}	
	IN1.close();

	// Open input file 2
        ifstream IN2(argv[2]);
        if(!IN2.is_open()) { cout << "Human Validated" << endl; exit(1); }

        while(getline(IN2,line))
        {
                stringstream DATA(line);
                string a;
                DATA >> a;
                DATA >> a;
		DATA >> a;

                bool flag=0;
                int k=-1;
                for(int i=0;i<TG.size();i++)
                {
                        if(TG[i]==a)
                        {
                        k=i;
                        flag=1;
                        break;
                        }
                }

                if(!flag)
                {
                TG.push_back(a);
                SC.push_back(1.0);
                }
                else
                {
                        if(SC[k]<1.0)
                        {
                        SC[k]=1.0;
                        }
                }

        }
        IN2.close();

	// Open input file 3
	ifstream IN3(argv[3]);
	if(!IN3.is_open()) { cout << "Mouse Predicted" << endl; exit(1); }	

	while(getline(IN3,line))
        {
                stringstream DATA(line);
                string a;
		DATA >> a; 
		DATA >> a;

		int b=0;
                for(int i=0;i<11;i++)
                {
                DATA >> b;
                }

                bool flag=0;
		int k=-1;
                for(int i=0;i<TG.size();i++)
                {
                        if(TG[i]==a)
                        {
                        k=i;
			flag=1;
                        break;
                        }
                }

                if(!flag)
                {
                TG.push_back(a);
                SC.push_back((double (b))/10);
                }
		else
		{
			if(SC[k]<((double (b))/10))	
			{
			SC[k]=((double (b))/10);
			}
		}

        }
	IN3.close();	

	// Open output file
        ofstream OUT(argv[4]);
        if(!OUT.is_open()) { cout << "Output" << endl; exit(1); }
	for(int i=0;i<TG.size();i++)
	{	
		OUT << TG[i] << "\t" << SC[i] << endl;
	}
	OUT.close();

return 0;
}
