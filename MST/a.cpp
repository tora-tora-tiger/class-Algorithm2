#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

struct UnionFind {
    vector<int> parent;
    int n;
    UnionFind(int n) : n(n) {
        parent.resize(n, -1);
    }
    int find(int x) {
        if (parent[x] < 0) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (parent[x] > parent[y]) swap(x, y);
        parent[y] = x;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    int size() {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (parent[i] < 0) cnt++;
        }
        return cnt;
    }
};

// make MST
int main() {
    int n, m; cin >> n >> m;
    UnionFind uf(n);
    using edge = pair<int, pair<int, int>>;
    priority_queue<edge, vector<edge>, greater<edge>> pq;
    for(int i = 0 ; i < m ; i++) {
        int w, u, v; cin >> w >> u >> v;
        pq.push({w, {u, v}});
    }

    vector<pair<int, pair<int, int>>> mst;
    int weight = 0;
    while(uf.size() > 1 && !pq.empty()) {
        auto [w, uv] = pq.top(); pq.pop();
        auto [u, v] = uv;
        if (uf.same(u, v)) continue;
        uf.unite(u, v);
        mst.push_back({w, {u, v}});
        weight += w;
    }
    
    // Output the edges in the MST
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "MST weight: " << weight << endl;
    cout << "MST edges:\n";
    for (auto [w, uv] : mst) {
        auto [u, v] = uv;
        cout << u << " " << v << " " << w << endl;
    }
}