
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int k = nums[0];

        bool asc = true, desc = true;

        for (int i = 0; i < n; i++) {
            if (nums[i] != (k + i) % n)
                asc = false;

            if (nums[i] != (k - i + n) % n)
                desc = false;
        }

        if (!asc && !desc)
            return -1;

        // State: (orientation, starting value)
        // orientation 0 = ascending, 1 = descending
        vector<int> dist(2 * n, -1);
        queue<int> q;

        int start = asc ? k : n + k;
        dist[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int state = q.front();
            q.pop();

            if (state == 0)
                return dist[state];

            int orientation = state / n;
            int x = state % n;

            // Rotate left by one
            int nextRotate;
            if (orientation == 0)
                nextRotate = (x + 1) % n;
            else
                nextRotate = n + (x - 1 + n) % n;

            if (dist[nextRotate] == -1) {
                dist[nextRotate] = dist[state] + 1;
                q.push(nextRotate);
            }

            // Reverse the entire array
            int nextReverse;
            if (orientation == 0)
                nextReverse = n + (x - 1 + n) % n;
            else
                nextReverse = (x + 1) % n;

            if (dist[nextReverse] == -1) {
                dist[nextReverse] = dist[state] + 1;
                q.push(nextReverse);
            }
        }

        return -1;
    }
};
