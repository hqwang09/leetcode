/*Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut. */

class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        if(n == 0 || n==1)
        {
            return 0;
        }
        vector<int> cuts(n+1,0);
        vector<vector<bool> > matrix(n, vector<bool>(n, false));
        for(int i = 0; i <= n; ++i)
        {
            cuts[i] = n-i;
        }
        for(int i = n-1; i>=0; --i)
        {
            for(int j = i; j <n; ++j)
            {
                if( (j-i < 2 && s[i] == s[j]) || 
                    (j-i >= 2 && matrix[i+1][j-1] && s[i] == s[j]) )
                {
                    matrix[i][j] = true;
                    cuts[i] = cuts[i] < (cuts[j+1]+1) ? cuts[i] : (cuts[j+1]+1);
                }
            }
        }
        return cuts[0]-1;
    }
};
