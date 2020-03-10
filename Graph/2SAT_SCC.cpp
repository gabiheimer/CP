#include<bits/stdc++.h>
#define endl '\n'
#define v_i vector<int>
#define v_vi vector<v_i>
#define s_i stack<int>

using namespace std;

void make_graphs(v_vi &clauses, v_vi &graph, v_vi &reverse, int nVars){
    // clauses[i][0] = primeira var da clausula
    // clauses[i][1] = segunda var da clausula
    // grafos vão ter tamanho 2*nVars+1 e as posicoes são 1-indexed
    // grafo[x] = grafo[x] e grafo[-x] = grafo[x+n]

    for(int i = 0; i < clauses.size(); i++){
        int n1 = clauses[i][0], n2 = clauses[i][1];
        if(n1 < 0) n1 = (-clauses[i][0]) + nVars;
        if(n2 < 0) n2 = (-clauses[i][1]) + nVars;

        // (n1 v n2) = 'n1 -> n2 / 'n2 -> n1
        if(n1 > nVars){
            graph[n1-nVars].push_back(n2);
            reverse[n2].push_back(n1-nVars);
        } else {
            graph[n1+nVars].push_back(n2);
            reverse[n2].push_back(n1+nVars);
        }

        if(n2 > nVars){
            graph[n2-nVars].push_back(n1);
            reverse[n1].push_back(n2-nVars);
        } else {
            graph[n2+nVars].push_back(n1);
            reverse[n1].push_back(n2+nVars);
        }
    }
}

void dfs(bool rev, int node, v_vi &graph, v_i &visited, s_i &order, v_i &scc, int counter){
    visited[node] = true;
    if(!rev) order.push(node);

    for(auto c : graph[node]){
        if(!visited[c]) dfs(rev, c, graph, visited, order, scc, counter);
    }

    if(rev) scc[node] = counter;
}

bool solve(){
    // ajeitar entrada

    v_vi graph(nVars*2+1), reverse(nVars*2+1), clauses;
    v_i visited(nVars*2+1), scc(nVars*2+1);
    s_i order;
    int counter = 0;

    make_graphs(clauses, graph, reverse, nVars);

    for(int i = 1; i < nVars*2+1; i++){
        if(!visited[i]) dfs(false, i, graph, visited, order, scc, counter);
    }

    visited.assign(nVars*2+1, false);
    while(!order.empty()){
        int node = order.top();
        order.pop();
        if(!visited[node]){
            dfs(true, node, reverse, visited, order, scc, counter);
            counter++;
        }
    }

    for(int i = 1; i <= nVars; i++){
        if(scc[i] == scc[i+nVars]) return false;
    }

    return true;
}