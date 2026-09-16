class Solution {
public:
    int numberOfSets(int n, int k) {
        const long long MOD = 1000000007;
        int N = n + k - 1;
        int R = 2 * k;

        vector<long long> fact(N + 1), invFact(N + 1);

        fact[0] = 1;
        for (int i = 1; i <= N; i++)
            fact[i] = fact[i - 1] * i % MOD;

        auto power = [&](long long a, long long b) {
            long long res = 1;
            while (b) {
                if (b & 1)
                    res = res * a % MOD;
                a = a * a % MOD;
                b >>= 1;
            }
            return res;
        };

        invFact[N] = power(fact[N], MOD - 2);

        for (int i = N; i >= 1; i--)
            invFact[i - 1] = invFact[i] * i % MOD;

        return fact[N] * invFact[R] % MOD * invFact[N - R] % MOD;
    }
};