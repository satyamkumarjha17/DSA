class Solution {
public:
    long long INF = 4e18;

    bool possible(long long mid,
                  vector<vector<int>>& edges,
                  vector<bool>& online,
                  long long k,
                  int n) {

        vector<vector<pair<int,int>>> g(n);
        vector<int> indeg(n, 0);

        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];

            if (w < mid) continue;
            if (u != 0 && u != n - 1 && !online[u]) continue;
            if (v != 0 && v != n - 1 && v != n - 1 && !online[v]) continue;

            g[u].push_back({v, w});
            indeg[v]++;
        }

        queue<int> q;
        for (int i = 0; i < n; i++)
            if (indeg[i] == 0) q.push(i);

        vector<long long> dist(n, INF);
        dist[0] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (auto &[v, w] : g[u]) {
                if (dist[u] != INF)
                    dist[v] = min(dist[v], dist[u] + w);

                if (--indeg[v] == 0)
                    q.push(v);
            }
        }

        return dist[n - 1] <= k;
    }

    int findMaxPathScore(vector<vector<int>>& edges,
                     vector<bool>& online,
                     long long k) {

        int n = online.size();

        long long lo = 0, hi = 1e9;
        int ans = -1;

        while (lo <= hi) {
            long long mid = lo + (hi - lo) / 2;

            if (possible(mid, edges, online, k, n)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return ans;
    }
};