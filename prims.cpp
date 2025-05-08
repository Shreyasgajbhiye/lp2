#include <bits/stdc++.h>
using namespace std;

void primsalgo(vector<vector<pair<int, int>>> adj, int v)
{
    vector<bool> inMST(v);
    typedef pair<int, pair<int, int>> P;

    priority_queue<P, vector<P>, greater<P>> pq;

    pq.push({0, {0, -1}});

    vector<pair<int, int>> mst;
    int sum = 0;
    while (!pq.empty())
    {
        int wt = pq.top().first, node = pq.top().second.first, parent = pq.top().second.second;
        pq.pop();
        if (inMST[node])
            continue;
        inMST[node] = true;
        sum += wt;
        mst.push_back({parent, node});
        for (auto ele : adj[node])
        {
            int wt1 = ele.first, node1 = ele.second;
            if (!inMST[node1])
            {
                pq.push({wt1, {node1, node}});
            }
        }
    }

        cout << "Weight of Minimum spanning tree is : " << sum << endl;
        cout << "Minimum Spanning tree is : ";
        for (auto ele : mst)
        {
            cout << '(' << ele.first << ',' << ele.second << ')' << endl;
        }
}

