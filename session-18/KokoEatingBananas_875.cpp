/* leetcode-875
binary search on answers- minimizing.

class Solution {
public:
    bool isPossible(vector<int>& piles, int h, int k) {
        long long hours = 0;

        for (int i = 0; i < piles.size(); i++) {
            hours += piles[i] / k;
            if (piles[i] % k != 0)
                hours += 1;
        }

        return hours <= h;
    }

    int minEatingSpeed(vector<int>& piles, int h) {
        int low = 1;
        int high = *max_element(piles.begin(), piles.end());
        int ans = high;

        while (low <= high) {
            int mid = (low + high) / 2;

            if (isPossible(piles, h, mid)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }
};*/
