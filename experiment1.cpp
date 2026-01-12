// recurrence relation: 3T(n/2)+nlogn+n
// master theorem: case 1:a>b^k: t(n)=theta(n^log2(3))

#include <bits/stdc++.h>
using namespace std;

long long countOps = 0;

void complexRec(int n) {
    if (n <= 2) {
        return;
    }

    int p = n;
    while (p > 0) {
        vector<int> temp(n);
        for (int i = 0; i < n; i++) {
            temp[i] = i ^ p;
            countOps++;
        }
        p >>= 1;
    }

    vector<int> small(n);
    for (int i = 0; i < n; i++) {
        small[i] = i * i;
        countOps++;
    }

    reverse(small.begin(), small.end());

    complexRec(n / 2);
    complexRec(n / 2);
    complexRec(n / 2);
}

int main() {
    int n;
    cin >> n;

    complexRec(n);

    cout << countOps;
    return 0;
}