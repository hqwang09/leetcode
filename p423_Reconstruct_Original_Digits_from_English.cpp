/*
 * p423_Reconstruct_Original_Digits_from_English.cpp
 *
 *  Created on: Oct 21, 2016
 *      Author: redwall

Given a non-empty string containing an out-of-order English representation of digits 0-9, output the digits in ascending order.

Note:

    Input contains only lowercase English letters.
    Input is guaranteed to be valid and can be transformed to its original digits. That means invalid inputs such as "abc" or "zerone" are not permitted.
    Input length is less than 50,000.

Example 1:

Input: "owoztneoer"

Output: "012"

Example 2:

Input: "fviefuro"

Output: "45"
 */
#include <string>
#include <map>
#include <vector>
#include <gtest/gtest.h>
namespace{
class Solution {
public:
    std::string originalDigits(std::string s) {
    	std::map<char, int> m;
    	std::vector<std::string> numStrs = {"zero", "two",
    			"six", "seven", "five", "eight", "three",
				"four", "one", "nine"};
    	std::vector<char> chs = {'z', 'w', 'x', 's', 'v', 'g', 'h', 'r', 'o', 'e'};
    	std::vector<int> nums = {0, 2, 6, 7, 5, 8, 3, 4, 1, 9};
    	for(int i = 0; i != s.size(); ++i)
    	{
    		//if(m.find(s[i]) == m.end())m[s[i]] = 1;
    		//else ++m[s[i]];
    		++m[s[i]];
    	}
    	std::string res;
    	std::vector<int> r(10,0);
    	for(int i = 0; i != 10; ++i)
    	{
    		int cnt = m[chs[i]];
    		if(cnt == 0)continue;
    		for(unsigned int j = 0; j != numStrs[i].size(); ++j)
    		{
    			m[numStrs[i][j]] -= cnt;
    		}
    		r[nums[i]] = cnt;
    	}
    	for(int i = 0; i != 10; ++i)
    	{
    		if(r[i] > 0)
    		{
    			for(int j = 0; j != r[i]; ++j)res += i + '0';
    		}
    	}
    	return res;
    }
    bool dfs(std::string& res, int k,
    		std::vector<std::string>& nums,
			std::map<char, int>& m, int total)
    {
    	std::cout<<"res = "<<res<<", k = "<<k<<", total = "<<total<<std::endl;
    	if(total == 0)return true;
    	if(k > 9)return false;
    	std::string s = nums[k];
        if(hasK(m, s))
        {
        	res.push_back(k+'0');
        	deleteM(m, s);
        	total -= s.size();
        }
        else
        {
        	k = k+1;
        }
      	if(dfs(res, k, nums, m, total)) return true;
      	else
      	{
      	    std::cout<<"to add res = "<<res<<", "<<*res.rbegin()-'0'<<std::endl;
            std::string t = nums[res.back()-'0'];
      	    addM(m, t);
            res.pop_back();
            total += t.size();
            return dfs(res, k+1, nums, m, total);
      	}
    }
    void addM(std::map<char, int>& m, const std::string& s)
    {
    	for(unsigned int i = 0; i != s.size(); ++i)m[s[i]]++;
    }
    void deleteM(std::map<char, int>& m, const std::string& s)
    {
    	for(unsigned int i = 0; i != s.size(); ++i)m[s[i]]--;
    }
    bool hasK(std::map<char, int>& m, const std::string& s)
    {
        for(unsigned int i = 0; i != s.size(); ++i)
        {
        	if(m[s[i]] == 0) return false;
        }
        return true;
    }
};
}//end of anonymous namespace

TEST(P423, OriginalDigits){
	Solution sl;
	std::string s1 = "owoztneoereno";
	std::string s2 = "etroezvenesigh";
	std::string s3 = "zeroonetwothreefourfivesixseveneightnine";
	EXPECT_EQ(sl.originalDigits(s1), "0112");
	EXPECT_EQ(sl.originalDigits(s2), "078");
	EXPECT_EQ(sl.originalDigits(s3), "0123456789");
}
