#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
	vector<string> generateParenthesis(int n) {
		string temp;
		vector<string> anser;
		helper(0, 0, temp, anser, "(", n);
		return anser;
	}

	void outPut(vector<string> ans)
	{
		for (int i = 0; i < ans.size(); i++)
		{
			cout << ans[i] << endl;
		}
	}

protected:
	void helper(int i, int j, string temp, vector<string> &ans, string s, int n)
	{
		temp += s;
		if (i < n - 1 && j < n)
		{
			helper(i + 1, j, temp, ans, "(", n);
		}
		if (j < n && j <= i)
		{
			helper(i, j + 1, temp, ans, ")", n);
		}
		if (j == n)
		{
			ans.push_back(temp);
			return;
		}
		return;
	}
};

int main()
{
	Solution s;
	s.outPut(s.generateParenthesis(4));
	system("pause");
	return 0;
}