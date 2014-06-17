#include <iostream>
using namespace std;

struct A{
	char a : 4;
	char b : 4;
};

void f()
{
	int c = 82;
	while (c--)
	{
		if (c / 9 % 3 != c % 9 % 3) cout << c / 9 << " " << c % 9 << endl;
	}
}

int main()
{
	f();
}