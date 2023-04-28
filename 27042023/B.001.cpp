#include <iostream>
#include <vector>

using namespace std;

// 10 3
// 4 5 9 1 8 6 10 2 3 7
// 1 

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        int wrong = 0;
        for (int i = 0; i < n; ++i) {
            int in;
            cin >> in;

            if (in % k != (i + 1) % k) {
                ++wrong;
            }
        }

        if (wrong == 0) {
            cout << 0 << endl;
            continue;
        }
        if (wrong <= 2) {
            cout << 1 << endl;
            continue;
        }
        cout << -1 << endl;
    }

    return 0;
}
