class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int start = 1, last = 1;
        int ans = INT_MIN;  

        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (start == 0) start = 1;
            if (last == 0) last = 1;

            start *= nums[i];
            last *= nums[n - i - 1];

            ans = max(ans, max(start, last));
        }
        return ans;
    }
};