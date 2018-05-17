#include <iostream>
using namespace std;

int main()
{
	cout << "hello world!" << endl;
	cout << "my first project" << endl;
	int*m = new int[4];
	for (int i = 0; i < sizeof(m)/4; ++i)
	{
		m[i] = i + 1;
	}
	system("pause");
	return 0;
}