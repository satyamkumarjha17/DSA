class Solution {
public:
    static const int MOD = 1e9 + 7;
    int n;
    vector<int> nums;
    int memo[205][201][201];

    int solve(int idx, int g1, int g2) {
        if (idx == n)
            return (g1 == g2 && g1 != 0);

        int &ans = memo[idx][g1][g2];
        if (ans != -1)
            return ans;

        ans = 0;

        ans = (ans + solve(idx + 1, g1, g2)) % MOD;
        ans = (ans + solve(idx + 1, std::gcd(g1, nums[idx]), g2)) % MOD;
        ans = (ans + solve(idx + 1, g1, std::gcd(g2, nums[idx]))) % MOD;

        return ans;
    }

    int subsequencePairCount(vector<int>& nums) {
        this->nums = nums;
        n = nums.size();

        memset(memo, -1, sizeof(memo));

        return solve(0, 0, 0);
    }
};