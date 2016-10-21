/*
Given a string that consists of only uppercase English letters,
you can replace any letter in the string with another letter
at most k times. Find the length of a longest substring
containing all repeating letters you can get after performing
the above operations.

Note:
Both the string's length and k will not exceed 104.

Example 1:

Input:
s = "ABAB", k = 2

Output:
4

Explanation:
Replace the two 'A's with two 'B's or vice versa.

Example 2:

Input:
s = "AABABBA", k = 1

Output:
4

Explanation:
Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.
*/

#include <string>
#include <map>
#include <algorithm>
#include <gtest/gtest.h>
namespace
{
class Solution {
public:
    int characterReplacement(std::string s, int k) {
    	int res = 0;
    	for(char a = 'A'; a <= 'Z'; ++a)
    	{
    		res = std::max(res, findLong(s, k, a));
    	}
    	return res;
    }
    int findLong(const std::string& s, int k, char a)
    {
    	int ia = 0, n = s.size();
    	int j = 0, ct = 0, res = 0;
    	while(j<n)
    	{
    		if(s[j] != a)
    		{
    			if(ct == k)
    			{
    				res = std::max(res, j-ia);
    				while(s[ia] == a)++ia;
    				++ia;
    			}
    			else
    			{
    				++ct;
    			}
    		}
    		++j;
    	}
    	res = std::max(res, j-ia);
    	return res;
    }
};
}

TEST(P424_FindLongTest, LeetCodeExamples){
	Solution sl;
	std::string s1 = "ABAB", s2 = "AABABBA";
	EXPECT_EQ(sl.findLong(s1, 2, 'C'), 2);
	EXPECT_EQ(sl.findLong(s1, 2, 'A'), 4);
	EXPECT_EQ(sl.findLong(s2, 1, 'A'), 4);
	EXPECT_EQ(sl.findLong(s2, 1, 'B'), 4);
}

