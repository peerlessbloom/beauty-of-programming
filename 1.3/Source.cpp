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
		if (m_CakeArray) delete[] m_CakeArray;
        if (m_ReverseCakeArray) delete[] m_ReverseCakeArray;
        if (m_SwapArray) delete[] m_SwapArray;
        if (m_ReverseCakeArraySwap) delete[] m_ReverseCakeArraySwap;
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
		m_nMaxSwap = UpBound();
		m_SwapArray = new int[m_nMaxSwap + 1];
		m_ReverseCakeArraySwap = new int[m_nMaxSwap];
	}
	int UpBound()
	{
        int count = 0;
        int index = m_nCakeCnt - 1;
        while (true)
        {
            while (index > 0 && m_CakeArray[index] == index) {
                index--;
            }
            if (index <= 0) break;
            int revertPos = index;
            while (revertPos > 0 && m_CakeArray[revertPos] != index) {
                revertPos--;
            }
            if (revertPos != 0)
            {
                Revert(revertPos, m_CakeArray);
                count++;
            }
            Revert(index, m_CakeArray);
            count++;
        }
		return count;
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
			Revert(i, m_ReverseCakeArray);
			m_ReverseCakeArraySwap[step] = i;
			Search(step + 1);
			Revert(i, m_ReverseCakeArray);
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
	void Revert(int deep, int * array)
	{
		int i, j, temp;
		for (i = 0, j = deep; i < j; i++, j--)
		{
			temp = array[i];
			array[i] = array[j];
			array[j] = temp;
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
int main()
{
	int nCakeCnt = 10;
	int nCakeArray[10] = { 3, 2, 1, 6, 5, 4, 9, 8, 7, 0 };
	CPrefixSorting sort;
	sort.run(nCakeArray, nCakeCnt);
	sort.Output();
	return 0;
}