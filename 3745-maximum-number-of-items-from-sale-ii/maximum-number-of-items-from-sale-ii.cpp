class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        vector<int> freq(n + 1, 0);

        long long minPrice = LLONG_MAX;

        for (auto &item : items) {
            freq[item[0]]++;
            minPrice = min(minPrice, (long long)item[1]);
        }

        vector<int> cnt(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j += i) {
                cnt[i] += freq[j];
            }
        }

        vector<pair<long long, long long>> opportunities;

        for (auto &item : items) {
            int factor = item[0];
            long long price = item[1];

            opportunities.push_back({price, cnt[factor] - 1});
        }

        sort(opportunities.begin(), opportunities.end());

        long long remaining = budget;
        long long ans = 0;

        for (auto &[price, count] : opportunities) {
            if (price > 2 * minPrice) break;

            long long take = min(count, remaining / price);

            ans += 2 * take;
            remaining -= take * price;
        }

        ans += remaining / minPrice;

        return (int)ans;
    }
};
