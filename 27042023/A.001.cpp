#include <iostream>
#include <vector>

using namespace std;

int formula(int n, int k) {
    return ((n - k) * (n - k - 1) / 2 + k * (k - 1) / 2);
}

int getK(int n, int k) {
    int kmin = 0;
    int kmax = n / 2;

    while ((kmax - kmin) > 1) {
        int kavr = (kmin + kmax) / 2;
        if (k == formula(n, kavr))
            return kavr;
        if (k > formula(n, kavr))
            kmax = kavr;
        else
            kmin = kavr;
    }
    if (k == formula(n, kmin))
        return kmin;
    if (k == formula(n, kmax))
        return kmax;

    return -1;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        int kfit = getK(n, k);

        if (kfit < 0) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
            for (int i = 0; i < kfit; ++i)
                cout << "-1 ";
            for (int i = kfit; i < n; ++i)
                cout << "1 ";
            cout << endl;
        }
    }

    return 0;
}
