#include <iostream>
using namespace std;

int main() {
    int arr[] = {1, 2, 2, 2, 3, 4};
    int n = 6;
    int key = 2;

    int l = 0, r = n - 1;
    int lb = n, ub = n;

    // Lower bound (First position ≥ key)
    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (arr[mid] >= key) {
            lb = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    l = 0;
    r = n - 1;

    // Upper Bound (First position > key)
    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (arr[mid] > key) {
            ub = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    cout << "Lower Bound: " << lb << endl;
    cout << "Upper Bound: " << ub << endl;

    return 0;
}
