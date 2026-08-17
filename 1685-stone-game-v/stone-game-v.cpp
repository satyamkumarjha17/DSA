class Solution {
public:
    int dp[501][501];
    vector<int> prefix;

    int solve(vector<int>& stoneValue, int i, int j) {
        if (i == j)
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];

        int ans = 0;

        for (int k = i; k < j; k++) {
            int left = prefix[k + 1] - prefix[i];
            int right = prefix[j + 1] - prefix[k + 1];

            if (left < right) {
                ans = max(ans, left + solve(stoneValue, i, k));
            }
            else if (left > right) {
                ans = max(ans, right + solve(stoneValue, k + 1, j));
            }
            else {
                ans = max(ans, max(
                    left + solve(stoneValue, i, k),
                    right + solve(stoneValue, k + 1, j)
                ));
            }
        }

        return dp[i][j] = ans;
    }

    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();

        prefix.resize(n + 1, 0);

        for (int i = 0; i < n; i++)
            prefix[i + 1] = prefix[i] + stoneValue[i];

        memset(dp, -1, sizeof(dp));

        return solve(stoneValue, 0, n - 1);
    }
};