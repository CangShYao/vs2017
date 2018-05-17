#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
	vector<vector<int>> combine(int n, int k) {
		vector<vector<int>> answer;
		if (n == 0 || k == 0)
			return answer;
		vector<int> intStact;
		helper(n, k, intStact, answer, 1);
		return answer;
	}

protected:
	void helper(int n, int k, vector<int> &intStack, vector<vector<int>> &ans, int intStart)
	{
		if (k == 0)
		{
			ans.push_back(intStack);
			return;
		}
		for (int i = intStart; i <= n - k + 1; i++)
		{
			intStack.push_back(i);
			helper(n, k - 1, intStack, ans, i + 1);
			intStack.pop_back();
		}
	}
};

int main()
{
	Solution s;
	s.combine(4, 2);
	return 0;
}