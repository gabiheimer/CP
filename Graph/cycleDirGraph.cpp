#include<bits/stdc++.h>
#define endl '\n'

using namespace std;

bool dfs(int node, vector<vector<int>> &graph, vector<int> &state){
    // 0 -> not visited, 1 -> in stack, 2 -> finished
    if(state[node] == 1) return true;
    if(state[node] == 2) return false;

    state[node] = 1;
    for(int i = 0; i < graph[node].size(); i++){
        bool cycle = dfs(graph[node][i], graph, state);
        if(cycle) return true;
    }

    state[node] = 2;
    return false;
}

bool findCycle(vector<vector<int>> &graph){
    bool cycle;
    vector<int> state(graph.size());

    for(int i = 0; i < graph.size(); i++){
        if(state[i] == 0){
            cycle = dfs(i, graph, state);
            if(cycle) return true;
        }
    }

    return false;
}