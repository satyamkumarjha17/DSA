class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        // Coordinate compression
        vector<int> vals = nums;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        vector<int> a(n);

        for (int i = 0; i < n; i++) {
            a[i] = lower_bound(vals.begin(), vals.end(), nums[i])
                   - vals.begin();
        }

        // Build suffix array
        vector<int> sa(n), rank = a, temp(n);

        iota(sa.begin(), sa.end(), 0);

        for (int k = 1; k < n; k *= 2) {

            sort(sa.begin(), sa.end(), [&](int x, int y) {
                if (rank[x] != rank[y])
                    return rank[x] < rank[y];

                int rx = (x + k < n) ? rank[x + k] : -1;
                int ry = (y + k < n) ? rank[y + k] : -1;

                return rx < ry;
            });

            temp[sa[0]] = 0;

            for (int i = 1; i < n; i++) {
                int x = sa[i - 1];
                int y = sa[i];

                bool different =
                    rank[x] != rank[y] ||
                    (x + k < n ? rank[x + k] : -1) !=
                    (y + k < n ? rank[y + k] : -1);

                temp[y] = temp[x] + different;
            }

            rank = temp;

            if (rank[sa[n - 1]] == n - 1)
                break;
        }

        // Build LCP array
        vector<int> pos(n), lcp(n, 0);

        for (int i = 0; i < n; i++)
            pos[sa[i]] = i;

        int h = 0;

        for (int i = 0; i < n; i++) {
            int r = pos[i];

            if (r == 0) {
                h = 0;
                continue;
            }

            int j = sa[r - 1];

            while (i + h < n && j + h < n &&
                   a[i + h] == a[j + h]) {
                h++;
            }

            lcp[r] = h;

            if (h > 0)
                h--;
        }

        // Find minimum unique subarray length
        int ans = n;

        for (int i = 0; i < n; i++) {
            int common = max(
                i > 0 ? lcp[i] : 0,
                i + 1 < n ? lcp[i + 1] : 0
            );

            int len = common + 1;

            if (sa[i] + len <= n) {
                ans = min(ans, len);
            }
        }

        return ans;
    }
};