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
    std::string originalDigits2(std::string s) {
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
    std::string originalDigits(std::string s) {
        std::vector<int> count(10,0);
        std::string res;
        for(unsigned int i = 0; i != s.size(); ++i)
		{
			if(s[i] == 'z')++count[0];      //0
			else if(s[i] == 'w')++count[2]; //2
			else if(s[i] == 'x')++count[6]; //6
			else if(s[i] == 'u')++count[4]; //4
			else if(s[i] == 'g')++count[8]; //8

			else if(s[i] == 'h')++count[3]; //8, 3
			else if(s[i] == 'o')++count[1]; //0,1,2,4
			else if(s[i] == 'f')++count[5]; //4, 5
			else if(s[i] == 'v')++count[7]; //5, 7
			else if(s[i] == 'i')++count[9]; //5,6,8,9
		}
		count[3] -= count[8];
		count[1] -= count[0] + count[2] + count[4];
		count[5] -= count[4];
		count[7] -= count[5];
		count[9] -= count[5] + count[6] + count[8];
		for(int i = 0; i != 10; ++i)
		{
			for(int j = 0; j < count[i]; ++j)
			{
			    res.push_back('0'+i);
			}
		}
		return res;
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
