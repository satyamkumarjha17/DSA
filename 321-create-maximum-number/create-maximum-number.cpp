class Solution {
private:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        vector<int> st;
        int remove = nums.size() - k;

        for (int num : nums) {
            while (!st.empty() && st.back() < num && remove > 0) {
                st.pop_back();
                remove--;
            }

            st.push_back(num);
        }

        st.resize(k);

        return st;
    }

    bool greaterVector(vector<int>& nums1, int i,
                       vector<int>& nums2, int j) {
        while (i < nums1.size() && j < nums2.size() &&
               nums1[i] == nums2[j]) {
            i++;
            j++;
        }

        if (j == nums2.size())
            return true;

        if (i == nums1.size())
            return false;

        return nums1[i] > nums2[j];
    }

    vector<int> merge(vector<int>& nums1, vector<int>& nums2) {
        vector<int> result;
        int i = 0;
        int j = 0;

        while (i < nums1.size() || j < nums2.size()) {
            if (greaterVector(nums1, i, nums2, j)) {
                result.push_back(nums1[i++]);
            } else {
                result.push_back(nums2[j++]);
            }
        }

        return result;
    }

public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int> answer;

        int start = max(0, k - (int)nums2.size());
        int end = min(k, (int)nums1.size());

        for (int take1 = start; take1 <= end; take1++) {
            int take2 = k - take1;

            vector<int> part1 = maxSubsequence(nums1, take1);
            vector<int> part2 = maxSubsequence(nums2, take2);

            vector<int> candidate = merge(part1, part2);

            if (candidate > answer) {
                answer = candidate;
            }
        }

        return answer;
    }
};