#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
using namespace std;

struct Drink
{
	int Volume;
	int TotalCount;
	int Happiness;
	Drink(int v, int t, int h)
	{
		Volume = v;
		TotalCount = t;
		Happiness = h;
	}
};

vector<vector<Drink> > drinks;
void initialize()
{
	ifstream fin("drink.txt");
	int v,t,h;
	
	while(fin>>v>>t>>h)
	{
		while(drinks.size()<=v)
		{
			drinks.push_back(vector<Drink>());
		}
		drinks[v].push_back(Drink((int)pow(2,v),t,h));
	}
	fin.close();
}

const int MAXV=101;
int opt[MAXV];

// 动态规划
int GetMaxHappiness1OneDim(int V)
{
	vector<Drink> temp;
	for (int i=0; i<drinks.size(); ++i)
		for(int j=0; j<drinks[i].size(); ++j)
			temp.push_back(drinks[i][j]);
    
	int T = temp.size();
    
	// init
	for(int i=0; i<=T; ++i)
		opt[i] = 0;
    
	for (int i=T-1; i>=0; --i)
	{
		for(int j=V; j>=0; --j)
		{
			for (int k=0; k<=temp[i].TotalCount; ++k)
			{
				int v = temp[i].Volume*k;
				int h = temp[i].Happiness*k;
				if (v<=j && opt[j-v]+h>opt[j])
				{
					opt[j] = opt[j-v]+h;
				}
			}
		}
	}
	return opt[V];
}


int main()
{
    initialize();
    int res = GetMaxHappiness1OneDim(7);
    cout << res << endl;
}