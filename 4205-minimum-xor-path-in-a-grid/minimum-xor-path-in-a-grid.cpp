class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<bool>> dp(
            m, vector<bool>(n, false)
        );

        // Store possible XOR values for each cell.
        vector<vector<vector<bool>>> possible(
            m, vector<vector<bool>>(
                n, vector<bool>(1024, false)
            )
        );

        possible[0][0][grid[0][0]] = true;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0)
                    continue;

                if (i > 0) {
                    for (int x = 0; x < 1024; x++) {
                        if (possible[i - 1][j][x]) {
                            possible[i][j][x ^ grid[i][j]] = true;
                        }
                    }
                }

                if (j > 0) {
                    for (int x = 0; x < 1024; x++) {
                        if (possible[i][j - 1][x]) {
                            possible[i][j][x ^ grid[i][j]] = true;
                        }
                    }
                }
            }
        }

        for (int x = 0; x < 1024; x++) {
            if (possible[m - 1][n - 1][x])
                return x;
        }

        return 0;
    }
};