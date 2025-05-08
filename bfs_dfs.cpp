#include <bits/stdc++.h>
using namespace std;
class Graph{
    private:
    unordered_map<int, list<int>> adj;
    public:

    void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs_helper(int node, set<int> &visited){
        visited.insert(node);
        cout << node << " ";
        for(auto neighbour : adj[node]){
            if(visited.find(neighbour) == visited.end()){
                dfs_helper(neighbour, visited);
            }
        }
    }

    void dfs(int start){
        set<int> visited;
        cout << "DFS STARTED FROM NODE : " << start << " : ";
        dfs_helper(start, visited);
        cout << endl;
    }

    void bfs(int start){
        set<int> visited;
        queue<int> q;
        q.push(start);
        visited.insert(start);
        while(!q.empty()){
            int node = q.front();
            q.pop();
            cout << node << " ";
            for(int neighbour : adj[node]){
                if(visited.find(neighbour) == visited.end()){
                    q.push(neighbour);
                    visited.insert(neighbour);
                }
            }
        }
    }
};
int main()
{
    Graph g;
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    int choice, startNode;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Recursive DFS\n";
        cout << "2. Iterative DFS\n";
        cout << "3. BFS\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 3)
        {
            cout << "Enter the starting node: ";
            cin >> startNode;
        }

        switch (choice)
        {
        case 1:
            g.dfs(startNode);
            break;
        case 2:
            // g.dfs_iterative(startNode);
            break;
        case 3:
            g.bfs(startNode);
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
