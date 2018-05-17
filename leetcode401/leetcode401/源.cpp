#include <vector>
#include <string>
#include <iostream>
using namespace std;
class Solution {
public:
	vector<string> readBinaryWatch(int num) {
		vector<string> answer;
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 60; j++)
			{
				if (getNumberOfOne(i*64+j) == num)
				{
					answer.push_back(intToString(i, j));
				}
			}
		}
		return answer;
	}

	void outPut(vector<string> ans)
	{
		for (int i = 0; i < ans.size(); i++)
		{
			cout << ans[i] << endl;
		}
	}

protected:
	int getNumberOfOne(int x)
	{
		int y = 0;
		while (x)
		{
			if (x & 1)
				y++;
			x >>= 1;
		}
		return y;
	}

	string intToString(int x, int y)
	{
		string ans;
		ans.append(to_string(x));
		ans.append(":");
		if (y<10)
		{
			ans.append("0");
			ans.append(to_string(y));
		}
		else
		{
			ans.append(to_string(y));
		}
		return ans;
	}
};

int main()
{
	Solution s;
	int num = 1;
	s.outPut(s.readBinaryWatch(num));
	system("pause");
	return 0;
}