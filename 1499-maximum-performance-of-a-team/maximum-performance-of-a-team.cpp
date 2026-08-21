class Solution {
public:
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        const int MOD = 1e9 + 7;

        vector<pair<int, int>> engineers;

        for (int i = 0; i < n; i++) {
            engineers.push_back({efficiency[i], speed[i]});
        }

        sort(engineers.rbegin(), engineers.rend());

        priority_queue<int, vector<int>, greater<int>> minHeap;

        long long speedSum = 0;
        long long maxPerformance = 0;

        for (auto& engineer : engineers) {
            int currentEfficiency = engineer.first;
            int currentSpeed = engineer.second;

            minHeap.push(currentSpeed);
            speedSum += currentSpeed;

            if (minHeap.size() > k) {
                speedSum -= minHeap.top();
                minHeap.pop();
            }

            maxPerformance = max(
                maxPerformance,
                speedSum * currentEfficiency
            );
        }

        return maxPerformance % MOD;
    }
};