class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        int left = 0, right = 0;

        for (int x : nums) {
            left = max(left, x);
            right += x;
        }

        while (left < right) {
            int mid = left + (right - left) / 2;
            int sum = 0, parts = 1;

            for (int x : nums) {
                if (sum + x > mid) {
                    parts++;
                    sum = x;
                } else {
                    sum += x;
                }
            }

            if (parts <= k)
                right = mid;
            else
                left = mid + 1;
        }

        return left;
    }
};