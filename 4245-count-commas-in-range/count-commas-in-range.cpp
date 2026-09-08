class Solution {
public:
    int countCommas(int n) {
        int ans = 0;
        
        for (int start = 1000, commas = 1; start <= n; start *= 1000, commas++) {
            int end = min(n, start * 1000 - 1);
            
            ans += (end - start + 1) * commas;
        }
        
        return ans;
    }
};