class Solution {
    struct Group {
        int start, len;
    };

    struct SparseTable {
        vector<vector<int>> st;

        SparseTable() {}

        SparseTable(const vector<int>& a) {
            int n = a.size();
            if (n == 0) return;

            int K = __lg(n) + 1;
            st.assign(K, vector<int>(n));
            st[0] = a;

            for (int k = 1; k < K; k++) {
                for (int i = 0; i + (1 << k) <= n; i++) {
                    st[k][i] = max(st[k - 1][i],
                                   st[k - 1][i + (1 << (k - 1))]);
                }
            }
        }

        int query(int l, int r) {
            if (l > r) return 0;
            int k = __lg(r - l + 1);
            return max(st[k][l], st[k][r - (1 << k) + 1]);
        }
    };

    void getZeroGroups(const string& s,
                       vector<Group>& groups,
                       vector<int>& idx) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '0') {
                if (i > 0 && s[i - 1] == '0')
                    groups.back().len++;
                else
                    groups.push_back({i, 1});
            }
            idx.push_back((int)groups.size() - 1);
        }
    }

public:
    vector<int> maxActiveSectionsAfterTrade(string s,
                                            vector<vector<int>>& queries) {
        int ones = count(s.begin(), s.end(), '1');

        vector<Group> groups;
        vector<int> idx;
        getZeroGroups(s, groups, idx);

        if (groups.empty())
            return vector<int>(queries.size(), ones);

        vector<int> merge;
        for (int i = 0; i + 1 < groups.size(); i++)
            merge.push_back(groups[i].len + groups[i + 1].len);

        SparseTable st(merge);

        vector<int> ans;

        for (auto& q : queries) {
            int l = q[0], r = q[1];

            int left = (idx[l] == -1)
                           ? -1
                           : groups[idx[l]].len -
                                 (l - groups[idx[l]].start);

            int right = (idx[r] == -1)
                            ? -1
                            : r - groups[idx[r]].start + 1;

            int start = idx[l] + 1;
            int end = (s[r] == '1') ? idx[r] : idx[r] - 1;

            int best = ones;

            if (s[l] == '0' && s[r] == '0' &&
                idx[l] + 1 == idx[r]) {
                best = max(best, ones + left + right);
            } else if (start <= end - 1) {
                best = max(best, ones + st.query(start, end - 1));
            }

            if (s[l] == '0' &&
                idx[l] + 1 <= ((s[r] == '1') ? idx[r] : idx[r] - 1)) {
                best = max(best,
                           ones + left + groups[idx[l] + 1].len);
            }

            if (s[r] == '0' && idx[l] < idx[r] - 1) {
                best = max(best,
                           ones + right + groups[idx[r] - 1].len);
            }

            ans.push_back(best);
        }

        return ans;
    }
};
