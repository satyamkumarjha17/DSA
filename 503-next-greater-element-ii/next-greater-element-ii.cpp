class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<int>ans(nums.size(),-1);

        for (int i=0; i<nums.size(); i++) {
            for (int j=1; j<nums.size(); j++) {
                int index=(i+j) % nums.size();

                if(nums[index]>nums[i]){
                    ans[i]=nums[index];
                    break;
                }
            }
        }
        return ans;
    }
};