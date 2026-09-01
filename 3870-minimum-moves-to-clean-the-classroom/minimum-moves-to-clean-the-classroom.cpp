#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        vector<pair<int, int>> litter;

        int startRow = 0, startCol = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    startRow = i;
                    startCol = j;
                }

                if (classroom[i][j] == 'L') {
                    litter.push_back({i, j});
                }
            }
        }

        int k = litter.size();

        if (k == 0) {
            return 0;
        }

        vector<vector<int>> litterIndex(m, vector<int>(n, -1));

        for (int i = 0; i < k; i++) {
            int r = litter[i].first;
            int c = litter[i].second;
            litterIndex[r][c] = i;
        }

        int targetMask = (1 << k) - 1;

        vector<vector<vector<vector<bool>>>> visited(
            m,
            vector<vector<vector<bool>>>(
                n,
                vector<vector<bool>>(
                    energy + 1,
                    vector<bool>(1 << k, false)
                )
            )
        );

        queue<array<int, 5>> q;

        q.push({startRow, startCol, energy, 0, 0});
        visited[startRow][startCol][energy][0] = true;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {
            auto [r, c, remainingEnergy, mask, moves] = q.front();
            q.pop();

            if (mask == targetMask) {
                return moves;
            }

            if (remainingEnergy == 0) {
                continue;
            }

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                if (nr < 0 || nr >= m || nc < 0 || nc >= n) {
                    continue;
                }

                if (classroom[nr][nc] == 'X') {
                    continue;
                }

                int newEnergy = remainingEnergy - 1;
                int newMask = mask;

                if (classroom[nr][nc] == 'L') {
                    int index = litterIndex[nr][nc];
                    newMask |= (1 << index);
                }

                if (classroom[nr][nc] == 'R') {
                    newEnergy = energy;
                }

                if (!visited[nr][nc][newEnergy][newMask]) {
                    visited[nr][nc][newEnergy][newMask] = true;

                    q.push({
                        nr,
                        nc,
                        newEnergy,
                        newMask,
                        moves + 1
                    });
                }
            }
        }

        return -1;
    }
};