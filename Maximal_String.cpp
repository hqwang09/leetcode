/*
 *
Problem Description
Given a string A and integer B, what is maximal lexicographical stringthat can be made from A if you do atmost B swaps.

Problem Constraints
1 <= |A| <= 9

A contains only digits from 0 to 9.

1 <= B <= 5

Input Format
First argument is string A.

Second argument is integer B.

Output Format
Return a string, the naswer to the problem.

Example Input
Input 1:

A = "254"
B = 1
Input 2:

A = "254'
B = 2


Example Output
Output 1:

 524
Output 2:

 542
*/


void dfs(string A, int B, int i, string& res, string& AA){
    if(B == 0){
        if(A > res)res = A;
        return;
    }
    if(A[i] == AA[i]){
        dfs(A, B, i+1, res, AA);
        return;
    }
    char c = A[i];
    for(int j = i+1; j < A.size(); ++j){
        if(A[j] == AA[i]){
            swap(A[j], A[i]);
            dfs(A, B-1, i+1, res, AA);
            swap(A[j], A[i]);
        }
    }
}

string Solution::solve(string A, int B) {
    string AA(A);
    sort(AA.begin(), AA.end(), [](char a, char b)->bool{
        return a > b;
    });
    if(B >= A.size())return AA;
    string res;
    dfs(A, B, 0, res, AA);
    return res;
}
