#include<bits/stdc++.h>

// This can be used to find SCCs
// explanation: https://www.youtube.com/watch?v=RYaakWv5m6o

struct Node {
    int id, low;

    Node(int id, int low) {
        this->id = id;
        this->low = low;
    }
};

// the bridges are the edges that connect two different SCCs
// if the graph is directed you dont need to check the source
int findBridges(int cur, int source, int &nextId, vector<vector<int>> &graph, vector<Node*> &nodes, int &bridgeCount) {
    if(nodes[cur]) return nodes[cur]->low;

    nodes[cur] = new Node(nextId, nextId);
    nextId++;

    for(auto nb : graph[cur]) {
        if(nb != source) {
            int nbLow = findBridges(nb, cur, nextId, graph, nodes, bridgeCount);
            if(nbLow > nodes[cur]->low) bridgeCount++;
            else nodes[cur]->low = nbLow;
        }
    }

    return nodes[cur]->low;
}

int solve(vector<vector<int>>& graph) {
    // tarjan's algorithm
    if(!graph.size()) return 0;

    int size = graph.size(), count = 0, nextId = 0;
    vector<Node*> nodes(size, NULL);
    findBridges(0, -1, nextId, graph, nodes, count);

    // count is the amount of bridges
    // if you want the amount of SCCs, you can count de amount of different lows in the graph
    return count;
}