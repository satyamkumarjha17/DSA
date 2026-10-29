class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        vector<vector<int>> adj(n);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int LOG = 17;
        vector<vector<int>> up(LOG, vector<int>(n));
        vector<int> tin(n), tout(n), depth(n);
        vector<int> bit(n + 1, 0);
        int timer = 0;

        vector<int> parent(n, -1);
        vector<int> order;
        order.reserve(n);

        // Iterative DFS: Euler tour and parent/depth
        stack<pair<int, int>> st;
        st.push({0, 0});

        while (!st.empty()) {
            auto& [u, state] = st.top();

            if (state == 0) {
                tin[u] = timer++;
                order.push_back(u);
                up[0][u] = parent[u] == -1 ? u : parent[u];
            }

            if (state < (int)adj[u].size()) {
                int v = adj[u][state++];
                if (v == parent[u]) continue;

                parent[v] = u;
                depth[v] = depth[u] + 1;
                st.push({v, 0});
            } else {
                tout[u] = timer;
                st.pop();
            }
        }

        for (int j = 1; j < LOG; j++) {
            for (int u = 0; u < n; u++) {
                up[j][u] = up[j - 1][up[j - 1][u]];
            }
        }

        auto add = [&](int i, int val) {
            for (++i; i <= n; i += i & -i)
                bit[i] ^= val;
        };

        auto pref = [&](int i) {
            int res = 0;
            for (; i > 0; i -= i & -i)
                res ^= bit[i];
            return res;
        };

        auto updateNode = [&](int u, int val) {
            add(tin[u], val);
            if (tout[u] < n) add(tout[u], val);
        };

        for (int u = 0; u < n; u++) {
            updateNode(u, 1 << (s[u] - 'a'));
        }

        auto rootMask = [&](int u) {
            return pref(tin[u] + 1);
        };

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);

            int diff = depth[u] - depth[v];

            for (int j = 0; j < LOG; j++) {
                if (diff & (1 << j)) u = up[j][u];
            }

            if (u == v) return u;

            for (int j = LOG - 1; j >= 0; j--) {
                if (up[j][u] != up[j][v]) {
                    u = up[j][u];
                    v = up[j][v];
                }
            }

            return up[0][u];
        };

        vector<bool> ans;

        for (const string& q : queries) {
            stringstream ss(q);
            string type;
            int u;
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int oldMask = 1 << (s[u] - 'a');
                int newMask = 1 << (c - 'a');

                updateNode(u, oldMask ^ newMask);
                s[u] = c;
            } else {
                int v;
                ss >> v;

                int w = lca(u, v);

                int mask = rootMask(u) ^ rootMask(v)
                         ^ (1 << (s[w] - 'a'));

                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};