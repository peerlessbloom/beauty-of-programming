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

bool compare(Drink a, Drink b)
{
    return a.Happiness > b.Happiness;
}

//greedy
int GetMaxHappiness2(int v)
{
    int happiness = 0;
    int i = 0;
    drinks.push_back(vector<Drink>());
    for (; i < drinks.size() - 1; i++)
    {
        if (drinks[i].size() == 0) continue;
        sort(drinks[i].begin(), drinks[i].end(), compare);
        int num = 0;
        if (v & 1)
        {
            while (drinks[i][num].TotalCount < 1)   num++;
            drinks[i][num].TotalCount -= 1;
            happiness += drinks[i][num].Happiness;
            if (drinks[i][num].TotalCount < 1)
                num++;
        }
        int pre = 0;
        for (; num < drinks[i].size(); num++)
        {
            if (drinks[i][num].TotalCount % 2)
            {
                if (pre == 0)
                    pre = drinks[i][num].Happiness;
                else
                {
                    pre += drinks[i][num].Happiness;
                    drinks[i + 1].push_back(Drink(drinks[i][num].Volume*2, 1, pre));
                    pre = 0;
                }
                drinks[i][num].TotalCount -= 1;
            }
            if (drinks[i][num].TotalCount > 0)
                drinks[i + 1].push_back(Drink(drinks[i][num].Volume*2, drinks[i][num].TotalCount/2, drinks[i][num].Happiness*2));
        }
        v >>= 1;
        drinks[i].clear();
    }
    return happiness;
}


int main()
{
    initialize();
    int res = GetMaxHappiness2(7);
    cout << res << endl;
}