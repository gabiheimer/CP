#include<bits/stdc++.h>
#define endl '\n'

using namespace std;

int maxSubArraySum(vector<int> nums){
    int maxSeq = nums[0];
    int maxTotal = nums[0];

    for(int i = 1; i < nums.size(); i++){
        maxSeq = max(maxSeq+nums[i], nums[i]);
        maxTotal = max(maxTotal, maxSeq);
    }

    return maxTotal;
}