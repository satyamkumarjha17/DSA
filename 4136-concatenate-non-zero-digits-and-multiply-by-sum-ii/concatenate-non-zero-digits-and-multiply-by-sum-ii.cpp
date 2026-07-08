class Solution {
public:
    static const int MOD = 1000000007;

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n = s.size();

        vector<int> digits, pos;
        for (int i = 0; i < n; i++) {
            if (s[i] != '0') {
                digits.push_back(s[i] - '0');
                pos.push_back(i);
            }
        }

        int k = digits.size();

        vector<long long> pow10(k + 1, 1);
        for (int i = 1; i <= k; i++)
            pow10[i] = (pow10[i - 1] * 10) % MOD;

        vector<long long> prefNum(k + 1, 0);
        vector<int> prefSum(k + 1, 0);

        for (int i = 0; i < k; i++) {
            prefNum[i + 1] = (prefNum[i] * 10 + digits[i]) % MOD;
            prefSum[i + 1] = prefSum[i] + digits[i];
        }

        vector<int> nextIdx(n, -1), prevIdx(n, -1);

        int p = 0;
        for (int i = 0; i < n; i++) {
            while (p < k && pos[p] < i) p++;
            if (p < k) nextIdx[i] = p;
        }

        p = k - 1;
        for (int i = n - 1; i >= 0; i--) {
            while (p >= 0 && pos[p] > i) p--;
            if (p >= 0) prevIdx[i] = p;
        }

        vector<int> ans;

        for (auto &q : queries) {
            int l = q[0], r = q[1];

            int L = nextIdx[l];
            int R = prevIdx[r];

            if (L == -1 || R == -1 || L > R) {
                ans.push_back(0);
                continue;
            }

            int len = R - L + 1;
            int sum = prefSum[R + 1] - prefSum[L];

            long long num = (prefNum[R + 1] -
                             prefNum[L] * pow10[len]) % MOD;
            if (num < 0) num += MOD;

            ans.push_back((num * sum) % MOD);
        }
        return ans;
    }
};