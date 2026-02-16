/*
Maximize the minimum distance between any two cows.
Time Complexity: O(n log m)
class Solution {
  public:
  
    bool isPossible(vector<int>& stalls, int k, int dist) {
        int count = 1;
        int last = stalls[0];
        
        for (int i = 1; i < stalls.size(); i++) {
            if (stalls[i] - last >= dist) {
                count++;
                last = stalls[i];
            }
            if (count >= k)
                return true;
        }
        return false;
    }
  
    int aggressiveCows(vector<int> &stalls, int k) {
        sort(stalls.begin(), stalls.end());
        
        int l = 1;
        int r = stalls.back() - stalls.front();
        int ans = 0;
        
        while (l <= r) {
            int mid = l + (r - l) / 2;
            
            if (isPossible(stalls, k, mid)) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        
        return ans;
    }
};


*/