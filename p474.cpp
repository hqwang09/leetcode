/*
 474. Ones and Zeroes

    Total Accepted: 3597
    Total Submissions: 10167
    Difficulty: Medium
    Contributors: piy9

In the computer world, use restricted resource you have to generate maximum benefit is what we always want to pursue.

For now, suppose you are a dominator of m 0s and n 1s respectively. On the other hand, there is an array with strings consisting of only 0s and 1s.

Now your task is to find the maximum number of strings that you can form with given m 0s and n 1s. Each 0 and 1 can be used at most once.

Note:

    The given numbers of 0s and 1s will both not exceed 100
    The size of given string array won't exceed 600.

Example 1:

Input: Array = {"10", "0001", "111001", "1", "0"}, m = 5, n = 3
Output: 4

Explanation: This are totally 4 strings can be formed by the using of 5 0s and 3 1s, which are “10,”0001”,”1”,”0”

Example 2:

Input: Array = {"10", "0", "1"}, m = 1, n = 1
Output: 2

Explanation: You could form "10", but then you'd have nothing left. Better form "0" and "1".
*/
#include <vector>
#include <algorithm>
#include <string>
#include <gtest/gtest.h>
namespace{
using namespace std;
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int> > dp(m+1, vector<int>(n+1, 0));
        vector<int> z(strs.size(),0), y(strs.size(), 0);
        int ns = strs.size();
        for(int i = 0; i < ns; ++i)
        {
            for(int j = 0; j < strs[i].size(); ++j)
            {
                if(strs[i][j] == '0')
                {
                    ++z[i];
                }
            }
            y[i] = strs[i].size() - z[i];
        }
        
        for(int k = 0; k < ns; ++k)
        {
            for(int i = m; i >= z[k]; --i)
            {
                for(int j = n; j >= y[k]; --j)
                {
                    dp[i][j] = max(dp[i][j], dp[i-z[k]][j-y[k]] + 1);
                }
            }
        }
        return dp[m][n];
    }
};
}//end of namespace
TEST(P474, OnesAndZeros){
	Solution sl;
	std::vector<std::string> s1 = {"10","0001","111001","1","0"};
	EXPECT_EQ(sl.findMaxForm(s1, 5,3), 4);
}
