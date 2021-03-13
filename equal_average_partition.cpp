/*
Equal Average Partition
Problem Description

Given an array A with non negative numbers, divide the array into two parts such that the average of both the parts is equal.

Return both parts (If exist). If there is no solution. return an empty list.

NOTE:

If a solution exists, you should return a list of exactly 2 lists of integers A and B which follow the following condition :
numElements in A <= numElements in B
If numElements in A = numElements in B, then A is lexicographically smaller than B ( https://en.wikipedia.org/wiki/Lexicographical_order )
If multiple solutions exist, return the solution where length(A) is minimum. If there is still a tie, return the one where A is lexicographically smallest.

Array will contain only non negative numbers.



**Input Format**
First andonly argument is an integer array A.



**Output Format**
Return 2D array consisting of two rows where each row denoted a partition.



**Example Input**
Input 1:

 A = [1 7 15 29 11 9]


Example Output
Output 1:

 [9 15] [1 7 11 29]


Example Explanation
Explanation 1:

 The average of part is (15+9)/2 = 12, average of second part elements is (1 + 7 + 11 + 29) / 4 
 */
bool lexcomp(vector<int>& a, vector<int>& b){
    for(int i = 0; i < a.size(); ++i){
        if(a[i] < b[i])return true;
        else if(a[i] > b[i])return false;
    }
    return true;
}

vector<int> findSum(vector<int>& A, int target, int m){
    vector<vector<vector<int>>> dp(target+1, vector<vector<int>>(m+1));
    for(int i = 0; i < A.size(); ++i){
        if(A[i] > target)break;
        for(int sum = target; sum >= A[i]; --sum){
            for(int k = m; k > 1; --k){
                //if(k == 2 & sum - A[i] == A[i])continue;
                if(dp[sum-A[i]][k-1].size() > 0){
                    vector<int> temp = dp[sum-A[i]][k-1];
                    temp.push_back(A[i]);
                    if(dp[sum][k].size() == 0 || lexcomp(temp, dp[sum][k]))
                    {
                        dp[sum][k] = temp;
                    }
                }
            }
        }
        if(dp[A[i]][1].size() == 0){
            dp[A[i]][1] = {A[i]};
        }
    }
    return dp[target][m];
}

vector<int> getSecond(vector<int>& A, vector<int>& first){
    unordered_multiset<int> s(A.begin(), A.end());
    for(int i : first){
        auto it = s.find(i);
        if(it != s.end()){
            s.erase(it);
        }
    }
    vector<int> second;
    for(int i : s){
        second.push_back(i);
    }
    sort(second.begin(), second.end());
    return second;
}

vector<vector<int> > Solution::avgset(vector<int> &A) {
    int sum = 0, n = A.size(), m = n/2;
    for(int i = 0; i < n; ++i){
        sum += A[i];
    }
    sort(A.begin(), A.end());
    vector<vector<int>> res;
    vector<int> first;
    for(int s = 1; s <= m; ++s){
        if(sum * s % n != 0)continue;
        int target = sum * s / n;
        first = findSum(A, target, s);
        if(first.size() != 0){
            vector<int> second = getSecond(A, first);
            res.push_back(first);
            res.push_back(second);
            return res;
        }
    }
    return res;
}

