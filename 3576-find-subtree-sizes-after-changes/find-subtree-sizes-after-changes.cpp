class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> adj(n);

        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        vector<int> newParent = parent;

        int last[26];
        fill(last, last + 26, -1);

        vector<int> prev(n);

        stack<pair<int, int>> st;
        st.push({0, 0});

        while (!st.empty()) {
            auto [node, state] = st.top();
            st.pop();

            int c = s[node] - 'a';

            if (state == 0) {
                prev[node] = last[c];

                if (last[c] != -1) {
                    newParent[node] = last[c];
                }

                last[c] = node;

                st.push({node, 1});

                for (int child : adj[node]) {
                    st.push({child, 0});
                }
            } 
            else {
                last[c] = prev[node];
            }
        }

        vector<vector<int>> newAdj(n);

        for (int i = 1; i < n; i++) {
            newAdj[newParent[i]].push_back(i);
        }

        vector<int> ans(n, 1);
        vector<int> order;
        stack<int> dfs;

        dfs.push(0);

        while (!dfs.empty()) {
            int node = dfs.top();
            dfs.pop();

            order.push_back(node);

            for (int child : newAdj[node]) {
                dfs.push(child);
            }
        }

        for (int i = n - 1; i > 0; i--) {
            int node = order[i];
            ans[newParent[node]] += ans[node];
        }

        return ans;
    }
};
