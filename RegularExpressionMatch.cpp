/*
 *
Regular Expression Match
Implement wildcard pattern matching with support for ‘?’ and ‘*’ for strings A and B.

’?’ : Matches any single character.
‘*’ : Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).
*/
int Solution::isMatch(const string A, const string B) {
    
    int na = A.size(), nb = B.size(), i = 0, j = 0;
        vector<vector<bool>> dp(na+1, vector<bool>(nb+1, false));
        dp[0][0] = true;
        for(int i = 0; i <= na; ++i){
            for(int j = 1; j <= nb; ++j){
                if(B[j-1] == '?'){
                    dp[i][j] = i == 0 ? false : dp[i-1][j-1];
                }
                else if(B[j-1] == '*'){
                    dp[i][j] = i == 0 ? dp[i][j-1] : (dp[i-1][j-1] || dp[i][j-1] || dp[i-1][j]);
                }
                else{
                    dp[i][j] = i == 0 ? false :  dp[i-1][j-1] && (A[i-1] == B[j-1]);
                }
            }
        }
        return dp[na][nb];
}
