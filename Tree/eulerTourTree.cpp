#include<bits/stdc++.h>

using namespace std;

class EulerTour {
    public:
    vector<int> inIdx, outIdx;
    int lastIdx;

    void fillArrays(int cur, vector<vector<int>> &tree) {
        inIdx[cur] = lastIdx++;        
        for(auto child : tree[cur]) fillArrays(child, tree);
        outIdx[cur] = lastIdx++;
    }

    EulerTour(vector<vector<int>> &tree, vector<bool> &isRoot) {
        inIdx.resize(tree.size());
        outIdx.resize(tree.size());
        lastIdx = 0;

        for(int i = 0; i < tree.size(); i++) {
            if(isRoot[i]) fillArrays(i, tree);
        }
    }

    // check if a is under b
    bool depends(int a, int b) {
        return inIdx[a] >= inIdx[b] && inIdx[a] <= outIdx[b];
    }
};