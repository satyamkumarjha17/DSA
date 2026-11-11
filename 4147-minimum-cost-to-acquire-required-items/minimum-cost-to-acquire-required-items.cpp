class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        
        long long c1 = cost1;
        long long c2 = cost2;
        long long cb = costBoth;
        long long n1 = need1;
        long long n2 = need2;

        long long ans = n1 * c1 + n2 * c2;

        long long common = min(n1, n2);

        long long cost = common * cb
                       + (n1 - common) * c1
                       + (n2 - common) * c2;

        ans = min(ans, cost);

        long long extra = max(n1, n2) * cb;

        ans = min(ans, extra);

        return ans;
    }
};
