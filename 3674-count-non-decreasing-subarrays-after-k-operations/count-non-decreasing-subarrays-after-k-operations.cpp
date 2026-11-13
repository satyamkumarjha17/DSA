class Solution {
public:
    using ll = long long;

    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int LOG = 1;

        while ((1 << LOG) <= n)
            LOG++;

        vector<ll> pref(n + 1, 0);

        for (int i = 0; i < n; i++)
            pref[i + 1] = pref[i] + nums[i];

        // Next greater element
        vector<int> nxt(n, n);
        stack<int> st;

        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.top()] <= nums[i])
                st.pop();

            if (!st.empty())
                nxt[i] = st.top();

            st.push(i);
        }

        // Binary lifting tables
        vector<vector<int>> up(LOG, vector<int>(n + 1, n));
        vector<vector<ll>> cost(LOG, vector<ll>(n + 1, 0));

        for (int i = 0; i < n; i++) {
            up[0][i] = nxt[i];

            cost[0][i] =
                1LL * nums[i] * (nxt[i] - i)
                - (pref[nxt[i]] - pref[i]);
        }

        // Sentinel initialization
        for (int j = 0; j < LOG; j++) {
            up[j][n] = n;
            cost[j][n] = 0;
        }

        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i < n; i++) {
                int mid = up[j - 1][i];

                up[j][i] = up[j - 1][mid];

                cost[j][i] =
                    cost[j - 1][i] +
                    cost[j - 1][mid];
            }
        }

        // Calculate operations required for [l, r]
        auto getCost = [&](int l, int r) -> ll {
            ll ans = 0;
            int p = l;

            for (int j = LOG - 1; j >= 0; j--) {
                int np = up[j][p];

                if (np <= r) {
                    ans += cost[j][p];
                    p = np;
                }
            }

            ans += 1LL * nums[p] * (r - p + 1)
                   - (pref[r + 1] - pref[p]);

            return ans;
        };

        // Binary search for each starting index
        ll answer = 0;

        for (int l = 0; l < n; l++) {
            int low = l, high = n - 1;
            int best = l - 1;

            while (low <= high) {
                int mid = low + (high - low) / 2;

                if (getCost(l, mid) <= k) {
                    best = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            answer += best - l + 1;
        }

        return answer;
    }
};
