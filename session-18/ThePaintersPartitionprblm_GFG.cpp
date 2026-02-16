/*
minimization problem using Binary Search on Answer: minimize the max time taken by painters
Time Complexity: O(n * log(sum(arr)))
class Solution {
  public:
  
    bool isPossible(vector<int>& arr, int k, long long maxTime) {
        long long sum = 0;
        int painters = 1;
        
        for (int i = 0; i < arr.size(); i++) {
            if (sum + arr[i] <= maxTime) {
                sum += arr[i];
            } else {
                painters++;
                sum = arr[i];
                
                if (painters > k)
                    return false;
            }
        }
        
        return true;
    }
  
    int minTime(vector<int>& arr, int k) {
        
        long long low = 0, high = 0;
        
        for (int i = 0; i < arr.size(); i++) {
            high += arr[i];
            low = max(low, (long long)arr[i]);
        }
        
        long long ans = high;
        
        while (low <= high) {
            long long mid = low + (high - low) / 2;
            
            if (isPossible(arr, k, mid)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        
        return ans;
    }
};
*/