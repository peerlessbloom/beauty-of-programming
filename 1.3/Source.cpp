#include <iostream>
using namespace std;
class CPrefixSorting
{
public:
	CPrefixSorting()
	{
		m_nCakeCnt = 0;
		m_nMaxSwap = 0;
	}
	~CPrefixSorting()
	{
		//Ignore
	}
	void run(int *pCakeArray, int nCakeCnt)
	{
		init(pCakeArray, nCakeCnt);
		m_nSearch = 0;
		Search(0);
	}
	void Output() const
	{
		cout << endl;
		for (int i = 0; i < m_nMaxSwap; i++)
		{
			cout << m_SwapArray[i] << " ";
		}
		cout << endl;
		cout << " |Search Times| : " << m_nSearch << endl;
		cout << "Total Swap times =  " << m_nMaxSwap << endl;
	}
private:
	void init(int *pCakeArray, int nCakeCnt)
	{
		m_nCakeCnt = nCakeCnt;
		m_CakeArray = new int[m_nCakeCnt];
		m_ReverseCakeArray = new int[m_nCakeCnt];
		for (int i = 0; i < m_nCakeCnt; i++)
		{
			m_CakeArray[i] = pCakeArray[i];
			m_ReverseCakeArray[i] = pCakeArray[i];
		}
		m_nMaxSwap = UpBound(m_nCakeCnt);
		m_SwapArray = new int[m_nMaxSwap + 1];
		m_ReverseCakeArraySwap = new int[m_nMaxSwap];
	}
	int UpBound(int nCakeCnt) const
	{
		return (nCakeCnt - 1) * 2 - 1;
	}
	int LowerBound() const
	{
		int temp, ret = 0;
		for (int i = 1; i < m_nCakeCnt; i++)
		{
			temp = m_ReverseCakeArray[i] - m_ReverseCakeArray[i - 1];
			if ((temp != 1) && (temp != -1))
			{
				ret++;
			}
		}
		return ret;
	}
	void Search(int step)
	{
		int i;
		m_nSearch++;
		if (m_nSearch % 1000 == 0)
		{
			cout << ".";
		}
		int nEstimate = LowerBound();
		if (step + nEstimate > m_nMaxSwap)
		{
			return;
		}
		if (IsSorted())
		{
			if (step < m_nMaxSwap)
			{
				m_nMaxSwap = step;
				for (i = 0; i < m_nMaxSwap; i++)
				{
					m_SwapArray[i] = m_ReverseCakeArraySwap[i];
				}
			}
			cout << "x";
			return;
		}
		for (i = 1; i < m_nCakeCnt; i++)
		{
			if (m_ReverseCakeArraySwap[step - 1] == i)
			{
				continue;
			}
			Revert(i);
			m_ReverseCakeArraySwap[step] = i;
			Search(step + 1);
			Revert(i);
		}
	}
	bool IsSorted()
	{
		for (int i = 1; i < m_nCakeCnt; i++)
		{
			if (m_ReverseCakeArray[i - 1] > m_ReverseCakeArray[i])
			{
				return false;
			}
		}
		return true;
	}
	void Revert(int deep)
	{
		int i, j, temp;
		for (i = 0, j = deep; i < j; i++, j--)
		{
			temp = m_ReverseCakeArray[i];
			m_ReverseCakeArray[i] = m_ReverseCakeArray[j];
			m_ReverseCakeArray[j] = temp;
		}
	}
private:
	int m_nCakeCnt;
	int* m_CakeArray;
	int* m_ReverseCakeArray;
	int m_nSearch;
	int m_nMaxSwap;
	int *m_SwapArray;
	int *m_ReverseCakeArraySwap;
};
int main1()
{
	int nCakeCnt = 10;
	int nCakeArray[10] = { 3, 2, 1, 6, 5, 4, 9, 8, 7, 0 };
	CPrefixSorting sort;
	sort.run(nCakeArray, nCakeCnt);
	sort.Output();
	return 0;
}