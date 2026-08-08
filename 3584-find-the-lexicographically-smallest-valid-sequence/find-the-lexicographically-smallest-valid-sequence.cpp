class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        vector<array<int, 26>> prev(n + 1);

        prev[0].fill(-1);

        for (int i = 1; i <= n; i++) {
            prev[i] = prev[i - 1];
            prev[i][word1[i - 1] - 'a'] = i - 1;
        }

        vector<int> exact(m + 1, -1);
        vector<int> one(m + 1, -1);

        exact[m] = n;
        one[m] = n;

        for (int j = m - 1; j >= 0; j--) {
            int p = exact[j + 1];

            if (p >= 0)
                exact[j] = prev[p][word2[j] - 'a'];

            p = one[j + 1];

            int match = -1;

            if (p >= 0)
                match = prev[p][word2[j] - 'a'];

            int mismatch = -1;

            if (exact[j + 1] >= 1)
                mismatch = exact[j + 1] - 1;

            one[j] = max(match, mismatch);
        }

        vector<int> ans;

        int pos = 0;
        bool usedMismatch = false;

        for (int j = 0; j < m; j++) {
            while (pos < n) {
                if (word1[pos] == word2[j]) {
                    if (one[j + 1] > pos) {
                        ans.push_back(pos);
                        pos++;
                        break;
                    }
                }
                else if (!usedMismatch) {
                    if (exact[j + 1] > pos) {
                        ans.push_back(pos);
                        pos++;
                        usedMismatch = true;
                        break;
                    }
                }

                pos++;
            }

            if (ans.size() != j + 1)
                return {};
        }

        return ans;
    }
};