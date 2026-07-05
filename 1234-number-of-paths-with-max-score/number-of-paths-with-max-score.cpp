class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        const int MOD = 1e9 + 7;

        vector<vector<int>> dp(n, vector<int>(n, -1));
        vector<vector<int>> ways(n, vector<int>(n, 0));

        dp[n-1][n-1] = 0;
        ways[n-1][n-1] = 1;

        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (board[i][j] == 'X') continue;
                if (i == n-1 && j == n-1) continue;

                int maxScore = -1;
                int count = 0;

                vector<pair<int,int>> dirs = {{1,0},{0,1},{1,1}};

                for (auto &d : dirs) {
                    int ni = i + d.first, nj = j + d.second;
                    if (ni < n && nj < n && dp[ni][nj] != -1) {
                        if (dp[ni][nj] > maxScore) {
                            maxScore = dp[ni][nj];
                            count = ways[ni][nj];
                        } else if (dp[ni][nj] == maxScore) {
                            count = (count + ways[ni][nj]) % MOD;
                        }
                    }
                }

                if (maxScore == -1) continue;

                int val = (board[i][j] == 'E') ? 0 : board[i][j] - '0';
                dp[i][j] = maxScore + val;
                ways[i][j] = count;
            }
        }

        if (ways[0][0] == 0) return {0, 0};
        return {dp[0][0], ways[0][0]};
    }
};