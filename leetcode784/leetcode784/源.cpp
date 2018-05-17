#include <vector>
#include <string>
#include <iostream>
// #include <>
using namespace std;

class Solution {
public:
	vector<string> letterCasePermutation(string S) {
		vector<string> strStack;
		string temp = S;
		helper(temp, 0, strStack);
		return strStack;
	}

	void outPut(vector<string> ans)
	{
		for (int i = 0; i < ans.size(); i++)
		{
			cout << ans[i] << endl;
		}
	}

protected:
	void helper(string S, int intStart, vector<string> &strStack)
	{
		if (S[intStart]>='A' && S[intStart] <='Z')
		{
			S[intStart] += 32;
			helper(S, intStart + 1, strStack);
			S[intStart] -= 32;
		}
		if (S[intStart] >= 'a' && S[intStart] <= 'z')
		{
			S[intStart] -= 32;
			helper(S, intStart + 1, strStack);
			S[intStart] += 32;
		}

		if (intStart == S.length())
		{
			strStack.push_back(S);
			return;
		}
		else
		{
			helper(S, intStart + 1, strStack);
		}
	}
};

int main()
{
	string str = "1bc4";
	Solution s;
	s.outPut(s.letterCasePermutation(str));
	system("pause");
	return 0;
}