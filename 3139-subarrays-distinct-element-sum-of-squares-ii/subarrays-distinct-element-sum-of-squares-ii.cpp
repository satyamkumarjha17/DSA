class Solution {
public:
    int sumCounts(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        vector<int> last(n + 1, -1);
        vector<long long> sum(4 * n), lazy(4 * n);
        vector<long long> sq(4 * n);

        auto update = [&](auto&& self, int node, int l, int r, int ql, int qr, int val) -> void {
            if (ql > r || qr < l) return;
            if (ql <= l && r <= qr) {
                long long len = r - l + 1;
                sq[node] = (sq[node] + 2LL * val * sum[node] + len * val * val) % MOD;
                sum[node] = (sum[node] + len * val) % MOD;
                lazy[node] += val;
                return;
            }
            int mid = (l + r) / 2;
            if (lazy[node]) {
                int v = lazy[node];
                self(self, node * 2, l, mid, l, mid, v);
                self(self, node * 2 + 1, mid + 1, r, mid + 1, r, v);
                lazy[node] = 0;
            }
            self(self, node * 2, l, mid, ql, qr, val);
            self(self, node * 2 + 1, mid + 1, r, ql, qr, val);
            sum[node] = (sum[node * 2] + sum[node * 2 + 1]) % MOD;
            sq[node] = (sq[node * 2] + sq[node * 2 + 1]) % MOD;
        };

        auto query = [&](auto&& self, int node, int l, int r, int ql, int qr) -> long long {
            if (ql > r || qr < l) return 0;
            if (ql <= l && r <= qr) return sq[node];
            int mid = (l + r) / 2;
            if (lazy[node]) {
                int v = lazy[node];
                auto apply = [&](int p, int left, int right) {
                    long long len = right - left + 1;
                    sq[p] = (sq[p] + 2LL * v * sum[p] + len * v * v) % MOD;
                    sum[p] = (sum[p] + len * v) % MOD;
                    lazy[p] += v;
                };
                apply(node * 2, l, mid);
                apply(node * 2 + 1, mid + 1, r);
                lazy[node] = 0;
            }
            return (self(self, node * 2, l, mid, ql, qr) +
                    self(self, node * 2 + 1, mid + 1, r, ql, qr)) % MOD;
        };

        long long ans = 0;
        unordered_map<int, int> prev;

        for (int i = 0; i < n; i++) {
            int l = prev.count(nums[i]) ? prev[nums[i]] + 1 : 0;
            update(update, 1, 0, n - 1, l, i, 1);
            ans = (ans + query(query, 1, 0, n - 1, 0, i)) % MOD;
            prev[nums[i]] = i;
        }

        return ans;
    }
};