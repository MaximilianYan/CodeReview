#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        map<int, int> factors;

        for (int i = 0; i < n; ++i) {
            int num;
            cin >> num;

            int factor = 2;
            int numq = num;
            while (num > 1) {
                if (num % factor) {
                    ++factor;
                    continue;
                }
                if (factor * factor > numq)
                    break;

                num /= factor;
                if (factors.count(factor) == 0) {
                    factors.insert(pair<int, int>(factor, 1));
                } else {
                    factors[factor]++;
                }
            }
            if (factors.count(num) == 0) {
                factors.insert(pair<int, int>(num, 1));
            } else {
                factors[num]++;
            }
        }

        int unquadr = 0;
        int quadr = 0;
        for (pair<int, int> fact : factors) {
            quadr += fact.second / 2;
            unquadr += fact.second % 2;
        }

        cout << quadr + (unquadr / 3) << endl;
    }

    return 0;
}
