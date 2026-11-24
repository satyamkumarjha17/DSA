class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int i = 0; i < n; i++) {
            long long product = 1;
            long long g = 0;
            long long l = 1;

            for (int j = i; j < n; j++) {
                long long x = nums[j];

                // Check before multiplying to avoid overflow
                if (product > 1e18 / x)
                    break;

                product *= x;
                g = gcd(g, x);
                l = l / gcd(l, x) * x;

                if (product == g * l) {
                    ans = max(ans, j - i + 1);
                }
            }
        }

        return ans;
    }
};
