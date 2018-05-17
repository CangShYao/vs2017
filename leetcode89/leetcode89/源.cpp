#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
	vector<int> grayCode(int n) {
		vector<int> answer;
		if (n > 0)
			helper(n, answer);
		else
			answer.push_back(0);
		return answer;
	}

protected:
	void helper(int n, vector<int> &ans)
	{
		if (n == 1)
		{
			ans.push_back(0);
			ans.push_back(1);
			return;
		}
		helper(n - 1, ans);
		int intSize = ans.size() - 1;
		for (int i = intSize; i >= 0; i--)
		{
			int num = ans[i] | (1 << (n - 1));
			ans.push_back(num);
		}
	}
};