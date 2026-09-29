class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();

        if (grid[0][0] == ')' || grid[m - 1][n - 1] == '(') return false;
        if ((m + n - 1) % 2) return false;

        vector<vector<vector<bool>>> dp(
            m, vector<vector<bool>>(n, vector<bool>(m + n, false))
        );

        dp[0][0][1] = true;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int bal = 0; bal <= m + n; bal++) {
                    if (!dp[i][j][bal] || bal < 0) continue;

                    if (i + 1 < m) {
                        int nb = bal + (grid[i + 1][j] == '(' ? 1 : -1);
                        if (nb >= 0)
                            dp[i + 1][j][nb] = true;
                    }

                    if (j + 1 < n) {
                        int nb = bal + (grid[i][j + 1] == '(' ? 1 : -1);
                        if (nb >= 0)
                            dp[i][j + 1][nb] = true;
                    }
                }
            }
        }

        return dp[m - 1][n - 1][0];
    }
};