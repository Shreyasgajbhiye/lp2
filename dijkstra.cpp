#include <bits/stdc++.h>
using namespace std;

void dijalgo(vector<vector<pair<int,int>>> adj,int v,int src){
    priority_queue<pair<int, int>, vector<pair<int, int>> , greater<>> pq;
    vector<int> dist(v, INT_MAX);
    dist[src] = 0;
    pq.push({0, src});
    while(!pq.empty()){
        int wt = pq.top().first;
        int v = pq.top().second;
        pq.pop();
        if(wt > dist[v]) continue;

        for(auto ele : adj[v]){
            int wt1 = ele.second;
            int v1 = ele.first;

            if(wt1+dist[v] < dist[v1]){
                dist[v1] = wt1+dist[v];
                pq.push({dist[v1], v1});
            }
        }

    }
    cout<<"Distance from the starting source : ";
    for(int ele : dist){
        cout<<ele<<" ";
    }
    
}

int main(){
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<pair<int, int>>> adj(V);
    cout << "Enter edges in the format: u v weight (0-based indexing)" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v, wt;
        cin >> u >> v >> wt;
        adj[u].emplace_back(v, wt);
        adj[v].emplace_back(u, wt); // For undirected graph
    }

    int src;
    cout << "Enter source vertex: ";
    cin >> src;

    dijalgo(adj,V, src);

    return 0;
}