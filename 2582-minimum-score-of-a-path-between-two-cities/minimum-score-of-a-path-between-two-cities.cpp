class Solution {
public:
    int ans = INT_MAX;

    void dfs(int node, vector<vector<pair<int,int>>>& adj, vector<int>& vis) {
        vis[node] = 1;

        for (auto &[next, dist] : adj[node]) {
            ans = min(ans, dist);

            if (!vis[next]) {
                dfs(next, adj, vis);
            }
        }
    }

    int minScore(int n, vector<vector<int>>& roads) {
        vector<vector<pair<int,int>>> adj(n + 1);

        for (auto &road : roads) {
            int u = road[0];
            int v = road[1];
            int d = road[2];

            adj[u].push_back({v, d});
            adj[v].push_back({u, d});
        }

        vector<int> vis(n + 1, 0);
        dfs(1, adj, vis);

        return ans;
    }
};