 /*
 440. K-th Smallest in Lexicographical Order

    Total Accepted: 493
    Total Submissions: 3258
    Difficulty: Hard
    Contributors: Stomach_ache

Given integers n and k, find the lexicographically k-th smallest integer in the range from 1 to n.

Note: 1 ≤ k ≤ n ≤ 109.

Example:

Input:
n: 13   k: 2

Output:
10

Explanation:
The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9], so the second smallest number is 10.
*/
#include <gtest/gtest.h>
#include <string>
#include <stdlib.h>
#include <iostream>
namespace
{
template <class T> int numDigits(T number)
{
	int digits = 0;
   	while(number)
   	{
   		number /= 10;
   		++digits;
   	}
   	return digits;
}

std::vector<int> buildCount(int m)
{
   	std::vector<int> incre(m, 1);
   	for(int i = 1; i < m; ++i)
   	{
   		incre[i] = 1 + 10 * incre[i-1];
   	}
   	return incre;
}

class Solution
{
public:
	int findKthNumber(int n, int k){
		std::string sn = std::to_string(n);
		int m = sn.size();
		std::vector<int> incre = buildCount(m);
		int res = 0;
		int nb = countBelow(sn, incre);
		if(k <= nb)
		{
			std::string sk = std::to_string(k);
			res = getKth(k, incre, m);
		}
		else
		{
			int nb1 = countBelow(sn.substr(0, m-1), incre);
		    int kk = k - nb + nb1;
		    std::string skk = std::to_string(kk);
		    std::cout<<"n = "<<n<<", k = "<<k<<", nb = "<<nb<<", nb1 = "<<nb1<<", kk="<<kk<<std::endl;
		    res = getKth(kk, incre, m-1);
		}
		return res;
	}

	int getKth(int n, std::vector<int>& incre, int m)
	{
		std::cout<<"getKth for "<<n<<", m = "<<m;
		int res = 0;
		for(int i = 0; i != m && n > 0; ++i)
		{
			int j = (n-1) / incre[m-i-1];
			if(i == 0)
			{
				res = j + 1;
			}
			else
			{
				res = res*10 + j;
			}
			n -= (j * incre[m-i-1] + 1);
		}
		std::cout<<", res = "<<res<<std::endl;
		return res;
	}
	int countBelow(const std::string s, std::vector<int>& incre)
	{
		int m = s.size();
		int res = 0;
		for(int i = 0; i != m; ++i)
		{
			if(i == 0)
			{
				res += incre[m-i-1] * (s[i] - '1');
			}
			else
			{
				res += incre[m-i-1] * (s[i] - '0');
			}
			res += 1;
		}
		return res;
	}
};

class Solution2 {//a slow version
public:
    int findKthNumber(int n, int k) {
        int m = numDigits(n);
        int i = 1, j = 1;
        while(i<k)
        {
        	j = getnext(j, m);
        	if(j <= n)++i;
        }
        return j;
    }
    int getnext(int j, int m)
    {//get next lexicographical number after j, but not with more than m digits
        int nj = numDigits(j);
        if(nj < m)return j*10;
        int res = j+1;
        while(res % 10 == 0)res /= 10;
        return res;
    }

};//2016 1027 0083 963


class Solution3
{
public:
    int findKthNumber(int n, int k) {
    	std::cout<<" ==== test n = "<<n<<", k = "<<k<<std::endl;
    	if(n<10)return k;
        std::string sn = std::to_string(n);
    	int m = sn.size();
    	std::vector<int> incre = buildCount(m);
    	std::string res;
    	int j = 0, kk = k, sum = 0;
    	for(int i = m-1; i >= 0; --i)
    	{
    		if(i == m-1) j = (sn[m-1-i]-'1') * incre[i] + 1;
    		else j = (sn[m-1-i]-'0') * incre[i] + 1;
    	    sum += j;
    	}
    	if(sum >= k)
    	{
    		std::cout<<"nEnough, to find k = "<<k<<", m = "<<m<<std::endl;
    		res = getKNoLimit(k, m, 1, incre);
    	}
    	else
    	{
    		std::cout<<"not enough, remain k-sum = "<<k-sum<<", m-1 = "<<m-1
    				<<", base = "<<sn[0]-'0'+1<<std::endl;
    		kk = k - sum;
    		for(int i = 0; i < m-1; ++i)
    		{
    			int km = incre[i] * ('9'-sn[m-2-i]);
    			if(kk <= km)
    			{
    				std::string t = getKNoLimit(kk, i+1, sn[m-2-i]-'0'+1, incre);
    				res = sn.substr(0, m-i-2) + t;
    				kk = 0;
    				break;
    			}
    			else
    			{
    				kk -= km;
    			}
    		}
    		if(kk > 0)
    		{
    		    res = getKNoLimit(kk, m-1, sn[0]-'0'+1, incre);
    		}
    	}
    	int ires = atoi(res.c_str());
    	std::cout<<" ----- ires = "<<ires<<std::endl;
    	return ires;
    }
    std::string getKNoLimit(int k, int m, int b, const std::vector<int>& incre)
    {
   		std::string res = std::string(1,b+'0');
   		int j = 0;
    	for(int i = m-1; i >= 0; --i)
   		{
   			k -= 1;
    		if(k == 0)
    		{
    			res.push_back(' ');
    			break;
    		}
    		j = k / incre[i];
    		res.back() += j;
    		res.push_back('0');
    		k -= j * incre[i];
   		}
    	res.pop_back();
    	return res;
    }


};

}//end of namespace
/*
TEST(P440, GetNext){
	Solution2 sl;
	int m = 4;
	EXPECT_EQ(sl.getnext(109, m), 1090);
	EXPECT_EQ(sl.getnext(1,m), 10);
	EXPECT_EQ(sl.getnext(1099, m), 11);
	EXPECT_EQ(sl.getnext(1,1),2);
}*/
TEST(P440, FindKthNumber)
{
	Solution sl;
	EXPECT_EQ(sl.findKthNumber(13,2), 10);
	EXPECT_EQ(sl.findKthNumber(2,2), 2);
	EXPECT_EQ(sl.findKthNumber(804289384, 42641503), 138377349);
	EXPECT_EQ(sl.findKthNumber(100,10), 17);
	EXPECT_EQ(sl.findKthNumber(100,90), 9);
//	EXPECT_THAT({1,2,4}, ::testing::ContainerEq({1,2,4}));
}
