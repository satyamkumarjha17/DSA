// class Solution {
// public:
//     vector<int> maxSlidingWindow(vector<int>& nums, int k) {
//         deque<int> dq;
//         vector<int> ans;

//         for (int i = 0; i < nums.size(); i++) {
//             while (!dq.empty() && dq.front() <= i - k)
//                 dq.pop_front();

//             while (!dq.empty() && nums[dq.back()] <= nums[i])
//                 dq.pop_back();

//             dq.push_back(i);

//             if (i >= k - 1)
//                 ans.push_back(nums[dq.front()]);
//         }

//         return ans;
//     }
// };

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ans(n - k + 1);

        int* index = new int[n];
        int left = 0;
        int right = -1;

        for (int i = 0; i < n; i++) {

            while (left <= right && index[left] <= i - k)
                left++;

            while (left <= right && nums[index[right]] <= nums[i])
                right--;

            index[++right] = i;

            if (i >= k - 1)
                ans[i - k + 1] = nums[index[left]];
        }

        delete[] index;

        return ans;
    }
};