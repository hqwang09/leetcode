/*
You’re given a read only array of n integers. Find out if any integer occurs more than n/3 times in the array in linear time and constant additional space.

If so, return the integer. If not, return -1.

If there are multiple solutions, return any one.
//*/

int Solution::repeatedNumber(const vector<int> &A) {
    // Do not write main() function.
    // Do not read input, instead use the arguments to the function.
    // Do not print the output, instead return values as specified
    // Still have a doubt. Checkout www.interviewbit.com/pages/sample_codes/ for more details
    int n = A.size(), n3 = n / 3;
    int r1 = 0, c1 = 0, r2 = 0, c2 = 0;
    for(int i = 0; i < n; ++i){
        if(A[i] == r1)++c1;
        else if(A[i] == r2)++c2;
        else if(c1 == 0){r1 = A[i], ++c1;}
        else if(c2 == 0){r2 = A[i], ++c2;}
        else {--c1; --c2;}
    }
    c1 = c2 = 0;
    for(int i = 0; i < n; ++i){
        if(A[i] == r1)++c1;
        if(A[i] == r2)++c2;
    }
    return c1 > n3 ? r1 : (c2 > n3 ? r2 : -1);
}
